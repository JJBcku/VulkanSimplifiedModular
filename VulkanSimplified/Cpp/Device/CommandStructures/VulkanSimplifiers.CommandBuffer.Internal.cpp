module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandBuffer.Internal;

AutoCleanUpCommandBuffer::AutoCleanUpCommandBuffer(const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
	const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
	WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) : _deviceRenderPassData(deviceRenderPassData), _sharedRenderPassData(sharedRenderPassData),
	_devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList), _windowList(windowList), _device(device),
	_buffer(buffer), _queue(queue)
{
}

AutoCleanUpCommandBuffer::~AutoCleanUpCommandBuffer()
{
}

void AutoCleanUpCommandBuffer::BeginRecording(CommandBufferUsage usage)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	
	switch (usage)
	{
	case CommandBufferUsage::MULTIPLE_USE_SIMULTANEOUS_USAGE:
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		break;
	case CommandBufferUsage::MULTIPLE_USE_NO_SIMULTANEOUS_USAGE:
		break;
	case CommandBufferUsage::ONE_USE:
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		break;
	default:
		throw std::runtime_error("AutoCleanUpCommandBuffer::BeginRecording Error: Program was giwen an erroneous command buffer usage value!");
	}

	if (vkBeginCommandBuffer(_buffer, &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("AutoCleanUpCommandBuffer::BeginRecording Error: Program failed to begin a command buffer's recording session!");
}

void AutoCleanUpCommandBuffer::EndRecording()
{
	if (vkEndCommandBuffer(_buffer) != VK_SUCCESS)
		throw std::runtime_error("AutoCleanUpCommandBuffer::BeginRecording Error: Program failed to end a command buffer's recording session!");
}

void AutoCleanUpCommandBuffer::BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID)
{
	vkCmdBindPipeline(_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _devicePipelineData.GetGraphicsPipeline(pipelineID));
}

void AutoCleanUpCommandBuffer::Draw(std::uint32_t vertexCount, std::uint32_t instanceCount, std::uint32_t firstVertex, std::uint32_t firstInstance)
{
	vkCmdDraw(_buffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

bool AutoCleanUpCommandBuffer::AcquireNextImage(std::uint64_t timeout, std::optional<IDObject<AutoCleanupSemaphore>> semaphoreID, std::optional<IDObject<AutoCleanupFence>> fenceID,
	std::uint32_t& returnIndex, IDObject<WindowPointer> windowID)
{
	auto& window = _windowList.GetWindowSimplifier(windowID);

	VkSemaphore semaphore = VK_NULL_HANDLE;
	VkFence fence = VK_NULL_HANDLE;

	if (semaphoreID.has_value())
		semaphore = _synchronizationList.GetSemaphore(semaphoreID.value());

	if (fenceID.has_value())
		fence = _synchronizationList.GetFence(fenceID.value());

	return window.AcquireNextImage(_device, timeout, semaphore, fence, returnIndex);
}

PrimaryNIRCommandBufferInternal::PrimaryNIRCommandBufferInternal(const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
	const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
	WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	AutoCleanUpCommandBuffer(deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
{
}

PrimaryNIRCommandBufferInternal::~PrimaryNIRCommandBufferInternal()
{
}

void PrimaryNIRCommandBufferInternal::BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID,
	std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height,
	const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers)
{
	VkRenderPassBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	beginInfo.renderPass = _deviceRenderPassData.GetRenderPass(renderPassID);
	beginInfo.framebuffer = _imageList.GetFramebuffer(framebufferID);

	beginInfo.renderArea.offset = { static_cast<std::int32_t>(startX), static_cast<std::int32_t>(startY) };
	beginInfo.renderArea.extent = { width, height };

	size_t maxSize = clearValues.size() << 1;
	if (maxSize <= clearValues.size())
		throw std::runtime_error("PrimaryNIRCommandBufferInternal::BeginRenderPass Error: Max size overflowed!");

	std::vector<VkClearValue> clearValuesList;
	clearValuesList.reserve(maxSize);

	for (auto& clearValue : clearValues)
	{
		if (clearValue.has_value())
		{
			auto value = _sharedRenderPassData.GetClearValue(clearValue.value());

			clearValuesList.push_back(value.first);
			if (value.second.has_value())
				clearValuesList.push_back(value.second.value());
		}
		else
		{
			clearValuesList.push_back(VkClearValue());
		}
	}

	beginInfo.clearValueCount = static_cast<std::uint32_t>(clearValuesList.size());
	beginInfo.pClearValues = clearValuesList.data();

	VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE;

	if (usesSecondaryBuffers)
		contents = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;

	vkCmdBeginRenderPass(_buffer, &beginInfo, contents);
}

void PrimaryNIRCommandBufferInternal::EndRenderPass()
{
	vkCmdEndRenderPass(_buffer);
}

SecondaryNIRCommandBufferInternal::SecondaryNIRCommandBufferInternal(const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
	const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
	WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	AutoCleanUpCommandBuffer(deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
{
}

SecondaryNIRCommandBufferInternal::~SecondaryNIRCommandBufferInternal()
{
}

PrimaryIRCommandBufferInternal::PrimaryIRCommandBufferInternal(const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
	const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
	WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	PrimaryNIRCommandBufferInternal(deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
{
}

PrimaryIRCommandBufferInternal::~PrimaryIRCommandBufferInternal()
{
}

void PrimaryIRCommandBufferInternal::BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID,
	std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height,
	const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers)
{
	VkRenderPassBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	beginInfo.renderPass = _deviceRenderPassData.GetRenderPass(renderPassID);
	beginInfo.framebuffer = _imageList.GetFramebuffer(framebufferID);

	beginInfo.renderArea.offset = { static_cast<std::int32_t>(startX), static_cast<std::int32_t>(startY) };
	beginInfo.renderArea.extent = { width, height };

	size_t maxSize = clearValues.size() << 1;
	if (maxSize <= clearValues.size())
		throw std::runtime_error("PrimaryNIRCommandBufferInternal::BeginRenderPass Error: Max size overflowed!");

	std::vector<VkClearValue> clearValuesList;
	clearValuesList.reserve(maxSize);

	for (auto& clearValue : clearValues)
	{
		if (clearValue.has_value())
		{
			auto value = _sharedRenderPassData.GetClearValue(clearValue.value());

			clearValuesList.push_back(value.first);
			if (value.second.has_value())
				clearValuesList.push_back(value.second.value());
		}
		else
		{
			clearValuesList.push_back(VkClearValue());
		}
	}

	beginInfo.clearValueCount = static_cast<std::uint32_t>(clearValuesList.size());
	beginInfo.pClearValues = clearValuesList.data();

	VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE;

	if (usesSecondaryBuffers)
		contents = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;

	vkCmdBeginRenderPass(_buffer, &beginInfo, contents);
}

void PrimaryIRCommandBufferInternal::EndRenderPass()
{
	vkCmdEndRenderPass(_buffer);
}

void PrimaryIRCommandBufferInternal::ResetCommandBuffer(bool freeResources)
{
	VkCommandBufferResetFlags flags = 0;
	if (freeResources)
		flags = VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT;

	vkResetCommandBuffer(_buffer, flags);
}

SecondaryIRCommandBufferInternal::SecondaryIRCommandBufferInternal(const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
	const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
	WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	SecondaryNIRCommandBufferInternal(deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
{
}

SecondaryIRCommandBufferInternal::~SecondaryIRCommandBufferInternal()
{
}

void SecondaryIRCommandBufferInternal::ResetCommandBuffer(bool freeResources)
{
	VkCommandBufferResetFlags flags = 0;
	if (freeResources)
		flags = VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT;

	vkResetCommandBuffer(_buffer, flags);
}