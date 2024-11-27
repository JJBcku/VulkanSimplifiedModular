module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandPool.Internal;

NIRCommandPoolInternal::NIRCommandPoolInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandPool commandPool, VkQueue queue,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity) : _core(core), _deviceRenderPassData(deviceRenderPassData),
	_sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList), _windowList(windowList),
	_device(device), _commandPool(commandPool), _queue(queue), _primaryBufferList(primaryBufferListInitialCapacity), _secondaryBufferList(secondaryBufferListInitialCapacity)
{
}

NIRCommandPoolInternal::~NIRCommandPoolInternal()
{
	if (_device != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(_device, _commandPool, nullptr);
	}
}

std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> NIRCommandPoolInternal::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("NIRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("NIRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_primaryBufferList.AddObject(std::make_unique<PrimaryNIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _windowList, _device, buffer, _queue), addOnReserve));
	}

	return ret;
}

std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> NIRCommandPoolInternal::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("NIRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("NIRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_secondaryBufferList.AddObject(std::make_unique<SecondaryNIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _windowList, _device, buffer, _queue), addOnReserve));
	}

	return ret;
}

PrimaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID)
{
	return *_primaryBufferList.GetObject(bufferID);
}

SecondaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID)
{
	return *_secondaryBufferList.GetObject(bufferID);
}

const PrimaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID) const
{
	return *_primaryBufferList.GetConstObject(bufferID);
}

const SecondaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID) const
{
	return *_secondaryBufferList.GetConstObject(bufferID);
}

void NIRCommandPoolInternal::ResetCommandPool(bool freeResources)
{
	VkCommandPoolResetFlags flags = 0;
	if (freeResources)
		flags = VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT;

	vkResetCommandPool(_device, _commandPool, flags);
}

bool NIRCommandPoolInternal::PresentSwapchainToQueue(IDObject<WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs, std::uint32_t imageIndex)
{
	auto& window = _windowList.GetWindowSimplifier(windowID);

	std::vector<VkSemaphore> semaphores;
	semaphores.reserve(waitSemaphoreIDs.size());

	for (auto& semaphore : waitSemaphoreIDs)
		semaphores.push_back(_synchronizationList.GetSemaphore(semaphore));

	VkSwapchainKHR swapchain = window.GetSwapchain();

	if (swapchain == VK_NULL_HANDLE)
		throw std::runtime_error("NIRCommandPoolInternal::PresentSwapchainToQueue Error: Program tried to present image from a non-existent swapchain!");

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = static_cast<std::uint32_t>(semaphores.size());
	presentInfo.pWaitSemaphores = semaphores.data();
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapchain;
	presentInfo.pImageIndices = &imageIndex;

	VkResult result = vkQueuePresentKHR(_queue, &presentInfo);

	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("NIRCommandPoolInternal::PresentSwapchainToQueue Error: Program failed to present a swapchain image to queue!");

	return result == VK_SUCCESS;
}

IRCommandPoolInternal::IRCommandPoolInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandPool commandPool, VkQueue queue,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity) : _core(core), _deviceRenderPassData(deviceRenderPassData),
	_sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList), _windowList(windowList),
	_device(device), _commandPool(commandPool), _queue(queue), _primaryBufferList(primaryBufferListInitialCapacity), _secondaryBufferList(secondaryBufferListInitialCapacity)
{
}

IRCommandPoolInternal::~IRCommandPoolInternal()
{
	if (_device != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(_device, _commandPool, nullptr);
	}
}

std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> IRCommandPoolInternal::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("IRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("IRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_primaryBufferList.AddObject(std::make_unique<PrimaryIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _windowList, _device, buffer, _queue), addOnReserve));
	}

	return ret;
}

std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> IRCommandPoolInternal::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("IRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("IRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_secondaryBufferList.AddObject(std::make_unique<SecondaryIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _windowList, _device, buffer, _queue), addOnReserve));
	}

	return ret;
}

PrimaryIRCommandBufferInternal& IRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID)
{
	return *_primaryBufferList.GetObject(bufferID);
}

SecondaryIRCommandBufferInternal& IRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID)
{
	return *_secondaryBufferList.GetObject(bufferID);
}

const PrimaryIRCommandBufferInternal& IRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID) const
{
	return *_primaryBufferList.GetConstObject(bufferID);
}

const SecondaryIRCommandBufferInternal& IRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID) const
{
	return *_secondaryBufferList.GetConstObject(bufferID);
}

void IRCommandPoolInternal::ResetCommandPool(bool freeResources)
{
	VkCommandPoolResetFlags flags = 0;
	if (freeResources)
		flags = VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT;

	vkResetCommandPool(_device, _commandPool, flags);
}

bool IRCommandPoolInternal::PresentSwapchainToQueue(IDObject<WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs, std::uint32_t imageIndex)
{
	auto& window = _windowList.GetWindowSimplifier(windowID);

	std::vector<VkSemaphore> semaphores;
	semaphores.reserve(waitSemaphoreIDs.size());

	for (auto& semaphore : waitSemaphoreIDs)
		semaphores.push_back(_synchronizationList.GetSemaphore(semaphore));

	VkSwapchainKHR swapchain = window.GetSwapchain();

	if (swapchain == VK_NULL_HANDLE)
		throw std::runtime_error("NIRCommandPoolInternal::PresentSwapchainToQueue Error: Program tried to present image from a non-existent swapchain!");

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = static_cast<std::uint32_t>(semaphores.size());
	presentInfo.pWaitSemaphores = semaphores.data();
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapchain;
	presentInfo.pImageIndices = &imageIndex;

	VkResult result = vkQueuePresentKHR(_queue, &presentInfo);

	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("NIRCommandPoolInternal::PresentSwapchainToQueue Error: Program failed to present a swapchain image to queue!");

	return result == VK_SUCCESS;
}