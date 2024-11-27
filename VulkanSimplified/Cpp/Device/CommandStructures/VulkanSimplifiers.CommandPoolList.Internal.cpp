module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandPoolList.Internal;

CommandPoolListInternal::CommandPoolListInternal(const LogicalDeviceCoreInternal& deviceCore, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, const CommandPoolListCreationData& creationData) : _deviceCore(deviceCore),
	_deviceRenderPassData(deviceRenderPassData), _sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList),
	_imageList(imageList), _windowList(windowList), _device(deviceCore.GetDevice()), _noIndividualResetCommandPoolList(creationData.noIndividualResetCommandPoolListInitialReservation),
	_individualResetCommandPoolList(creationData.individualResetCommandPoolListInitialReservation)
{
}

CommandPoolListInternal::~CommandPoolListInternal()
{
}

IDObject<std::unique_ptr<NIRCommandPoolInternal>> CommandPoolListInternal::AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	VkCommandPoolCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.queueFamilyIndex = _deviceCore.GetQueueFamily(queueID);

	if (frequentlyRedoneBuffers)
		createInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	VkCommandPool add = VK_NULL_HANDLE;

	if (vkCreateCommandPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("CommandPoolListInternal::AddCommandPoolWithoutIndividualReset Error: Program failed to create a command pool!");

	return _noIndividualResetCommandPoolList.AddObject(std::make_unique<NIRCommandPoolInternal>(_deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
		_synchronizationList, _imageList, _windowList, _device, add, _deviceCore.GetQueue(queueID),
		primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity), addOnReserve);
}

IDObject<std::unique_ptr<IRCommandPoolInternal>> CommandPoolListInternal::AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	VkCommandPoolCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.queueFamilyIndex = _deviceCore.GetQueueFamily(queueID);
	createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	if (frequentlyRedoneBuffers)
		createInfo.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	VkCommandPool add = VK_NULL_HANDLE;

	if (vkCreateCommandPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("CommandPoolListInternal::AddCommandPoolWithIndividualReset Error: Program failed to create a command pool!");

	return _individualResetCommandPoolList.AddObject(std::make_unique<IRCommandPoolInternal>(_deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
		_synchronizationList, _imageList, _windowList, _device, add, _deviceCore.GetQueue(queueID),
		primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity), addOnReserve);
}

NIRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID)
{
	return *_noIndividualResetCommandPoolList.GetObject(poolID);
}

IRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID)
{
	return *_individualResetCommandPoolList.GetObject(poolID);
}

const NIRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID) const
{
	return *_noIndividualResetCommandPoolList.GetConstObject(poolID);
}

const IRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID) const
{
	return *_individualResetCommandPoolList.GetConstObject(poolID);
}

void CommandPoolListInternal::SubmitBuffers(size_t queueID, const std::vector<CommandBufferSubmitInfo>& submitInfos, std::optional<IDObject<AutoCleanupFence>> fenceID)
{
	VkQueue queue = _deviceCore.GetQueue(queueID);

	if (submitInfos.empty())
		throw std::runtime_error("CommandPoolListInternal::SubmitBuffers Error: Program tried to submit no data!");

	std::vector<VkSubmitInfo> submitInfoList;
	std::vector<std::vector<VkSemaphore>> waitSemaphores;
	std::vector<std::vector<VkPipelineStageFlags>> pipelineStageFlags;
	std::vector<std::vector<VkCommandBuffer>> commandBuffers;
	std::vector<std::vector<VkSemaphore>> signalSemaphores;

	submitInfoList.reserve(submitInfos.size());
	waitSemaphores.resize(submitInfos.size());
	pipelineStageFlags.resize(submitInfos.size());
	commandBuffers.resize(submitInfos.size());
	signalSemaphores.resize(submitInfos.size());

	for (size_t i = 0; i < submitInfos.size(); ++i)
	{
		auto& submitInfo = submitInfos[i];

		VkSubmitInfo add{};
		add.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		if (submitInfos[i].commandBufferIDs.empty())
			throw std::runtime_error("CommandPoolListInternal::SubmitBuffers Error: Program tried to submit no commands buffer in a batch!");

		waitSemaphores[i].reserve(submitInfo.waitSemaphores.size());
		pipelineStageFlags[i].reserve(submitInfo.waitSemaphores.size());
		commandBuffers[i].reserve(submitInfo.commandBufferIDs.size());
		signalSemaphores[i].reserve(submitInfo.signalSemaphores.size());

		for (auto& waitSemaphoresData : submitInfo.waitSemaphores)
		{
			waitSemaphores[i].push_back(_synchronizationList.GetSemaphore(waitSemaphoresData.first));
			pipelineStageFlags[i].push_back(TranslateStageFlags(waitSemaphoresData.second));
		}

		add.waitSemaphoreCount = static_cast<std::uint32_t>(waitSemaphores[i].size());
		add.pWaitSemaphores = waitSemaphores[i].data();
		add.pWaitDstStageMask = pipelineStageFlags[i].data();

		for (auto& commandBufferID : submitInfo.commandBufferIDs)
		{
			commandBuffers[i].push_back(GetCommandBuffer(commandBufferID));
		}

		add.commandBufferCount = static_cast<std::uint32_t>(commandBuffers[i].size());
		add.pCommandBuffers = commandBuffers[i].data();

		for (auto& signalSemaphoresData : submitInfo.signalSemaphores)
		{
			signalSemaphores[i].push_back(_synchronizationList.GetSemaphore(signalSemaphoresData));
		}

		add.signalSemaphoreCount = static_cast<std::uint32_t>(signalSemaphores[i].size());
		add.pSignalSemaphores = signalSemaphores[i].data();

		submitInfoList.push_back(add);
	}

	VkFence fence = VK_NULL_HANDLE;
	if (fenceID.has_value())
		fence = _synchronizationList.GetFence(fenceID.value());

	if (vkQueueSubmit(queue, static_cast<std::uint32_t>(submitInfoList.size()), submitInfoList.data(), fence) != VK_SUCCESS)
		throw std::runtime_error("CommandPoolListInternal::SubmitBuffers Error: Program failed to submit command buffers to queue!");
}

VkCommandBuffer CommandPoolListInternal::GetCommandBuffer(CommandBufferGenericID bufferID) const
{
	VkCommandBuffer ret = VK_NULL_HANDLE;

	switch (bufferID.type)
	{
	case CommandBufferIDType::NIR_PRIMARY:
		ret = GetCommandBuffer(bufferID.NIRPrimaryID.commandPoolID, bufferID.NIRPrimaryID.commandBufferID);
		break;
	case CommandBufferIDType::NIR_SECONDARY:
		ret = GetCommandBuffer(bufferID.NIRSecondaryID.commandPoolID, bufferID.NIRSecondaryID.commandBufferID);
		break;
	case CommandBufferIDType::IR_PRIMARY:
		ret = GetCommandBuffer(bufferID.IRPrimaryID.commandPoolID, bufferID.IRPrimaryID.commandBufferID);
		break;
	case CommandBufferIDType::IR_SECONDARY:
		ret = GetCommandBuffer(bufferID.IRSecondaryID.commandPoolID, bufferID.IRSecondaryID.commandBufferID);
		break;
	default:
		throw std::runtime_error("CommandPoolListInternal::GetCommandBuffer Error: Program was given an erroneous command buffer ID type!");
	}

	return ret;
}

VkCommandBuffer CommandPoolListInternal::GetCommandBuffer(IDObject<std::unique_ptr<NIRCommandPoolInternal>> commandPoolID,
	IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> commandBufferID) const
{
	auto& commandPool = _noIndividualResetCommandPoolList.GetConstObject(commandPoolID);
	auto& commandBuffer = commandPool->GetPrimaryCommandBufferSimplifier(commandBufferID);

	return commandBuffer.GetCommandBuffer();
}

VkCommandBuffer CommandPoolListInternal::GetCommandBuffer(IDObject<std::unique_ptr<NIRCommandPoolInternal>> commandPoolID,
	IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> commandBufferID) const
{
	auto& commandPool = _noIndividualResetCommandPoolList.GetConstObject(commandPoolID);
	auto& commandBuffer = commandPool->GetSecondaryCommandBufferSimplifier(commandBufferID);

	return commandBuffer.GetCommandBuffer();
}

VkCommandBuffer CommandPoolListInternal::GetCommandBuffer(IDObject<std::unique_ptr<IRCommandPoolInternal>> commandPoolID,
	IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> commandBufferID) const
{
	auto& commandPool = _individualResetCommandPoolList.GetConstObject(commandPoolID);
	auto& commandBuffer = commandPool->GetPrimaryCommandBufferSimplifier(commandBufferID);

	return commandBuffer.GetCommandBuffer();
}

VkCommandBuffer CommandPoolListInternal::GetCommandBuffer(IDObject<std::unique_ptr<IRCommandPoolInternal>> commandPoolID,
	IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> commandBufferID) const
{
	auto& commandPool = _individualResetCommandPoolList.GetConstObject(commandPoolID);
	auto& commandBuffer = commandPool->GetSecondaryCommandBufferSimplifier(commandBufferID);

	return commandBuffer.GetCommandBuffer();
}