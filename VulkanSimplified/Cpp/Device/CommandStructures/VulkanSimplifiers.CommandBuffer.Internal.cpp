module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandBuffer.Internal;

AutoCleanUpCommandBuffer::AutoCleanUpCommandBuffer(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) : _core(core),
	_deviceRenderPassData(deviceRenderPassData), _sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList),
	_imageList(imageList), _windowList(windowList), _device(device), _buffer(buffer), _queue(queue)
{
}

AutoCleanUpCommandBuffer::~AutoCleanUpCommandBuffer()
{
}

VkCommandBuffer AutoCleanUpCommandBuffer::GetCommandBuffer() const
{
	return _buffer;
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

PrimaryNIRCommandBufferInternal::PrimaryNIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	AutoCleanUpCommandBuffer(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
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

void PrimaryNIRCommandBufferInternal::TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs,
	std::uint32_t imagesIndex)
{
	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.srcAccessMask = 0;
	barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	
	if (queuesIDs.has_value())
	{
		barrier.srcQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().first);
		barrier.dstQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().second);
	}

	auto& window = _windowList.GetWindowSimplifier(windowID);

	barrier.image = window.GetSwapchainImage(imagesIndex);
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	vkCmdPipelineBarrier(_buffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void PrimaryNIRCommandBufferInternal::TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex)
{
	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	if (queuesIDs.has_value())
	{
		barrier.srcQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().first);
		barrier.dstQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().second);
	}

	auto& window = _windowList.GetWindowSimplifier(windowID);

	barrier.image = window.GetSwapchainImage(imagesIndex);
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	vkCmdPipelineBarrier(_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void PrimaryNIRCommandBufferInternal::BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<AutoCleanup2DSimpleImage> imageID, std::uint32_t startX, std::uint32_t startY,
	std::uint32_t width, std::uint32_t height, std::uint32_t swapchainImageIndex)
{
	VkImageBlit blitData{};
	blitData.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	blitData.srcSubresource.mipLevel = 0;
	blitData.srcSubresource.baseArrayLayer = 0;
	blitData.srcSubresource.layerCount = 1;

	blitData.srcOffsets[0].x = static_cast<std::int32_t>(startX);
	blitData.srcOffsets[0].y = static_cast<std::int32_t>(startY);
	blitData.srcOffsets[0].z = 0;
	blitData.srcOffsets[1].x = static_cast<std::int32_t>(width);
	blitData.srcOffsets[1].y = static_cast<std::int32_t>(height);
	blitData.srcOffsets[1].z = 1;

	auto& window = _windowList.GetWindowSimplifier(windowID);

	blitData.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	blitData.dstSubresource.mipLevel = 0;
	blitData.dstSubresource.baseArrayLayer = 0;
	blitData.dstSubresource.layerCount = 1;

	blitData.dstOffsets[0].x = 0;
	blitData.dstOffsets[0].y = 0;
	blitData.dstOffsets[0].z = 0;
	blitData.dstOffsets[1].x = static_cast<std::int32_t>(window.GetWidth());
	blitData.dstOffsets[1].y = static_cast<std::int32_t>(window.GetHeight());
	blitData.dstOffsets[1].z = 1;

	vkCmdBlitImage(_buffer, _imageList.GetImage(imageID), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, window.GetSwapchainImage(swapchainImageIndex), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1, &blitData, VK_FILTER_LINEAR);
}

SecondaryNIRCommandBufferInternal::SecondaryNIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	AutoCleanUpCommandBuffer(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
{
}

SecondaryNIRCommandBufferInternal::~SecondaryNIRCommandBufferInternal()
{
}

PrimaryIRCommandBufferInternal::PrimaryIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	PrimaryNIRCommandBufferInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
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

void PrimaryIRCommandBufferInternal::TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex)
{
	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.srcAccessMask = 0;
	barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

	if (queuesIDs.has_value())
	{
		barrier.srcQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().first);
		barrier.dstQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().second);
	}

	auto& window = _windowList.GetWindowSimplifier(windowID);

	barrier.image = window.GetSwapchainImage(imagesIndex);
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	vkCmdPipelineBarrier(_buffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void PrimaryIRCommandBufferInternal::TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex)
{
	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	if (queuesIDs.has_value())
	{
		barrier.srcQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().first);
		barrier.dstQueueFamilyIndex = _core.GetQueueFamily(queuesIDs.value().second);
	}

	auto& window = _windowList.GetWindowSimplifier(windowID);

	barrier.image = window.GetSwapchainImage(imagesIndex);
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	vkCmdPipelineBarrier(_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void PrimaryIRCommandBufferInternal::BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<AutoCleanup2DSimpleImage> imageID, std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height, std::uint32_t swapchainImageIndex)
{
	VkImageBlit blitData{};
	blitData.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	blitData.srcSubresource.mipLevel = 0;
	blitData.srcSubresource.baseArrayLayer = 0;
	blitData.srcSubresource.layerCount = 1;

	blitData.srcOffsets[0].x = static_cast<std::int32_t>(startX);
	blitData.srcOffsets[0].y = static_cast<std::int32_t>(startY);
	blitData.srcOffsets[0].z = 0;
	blitData.srcOffsets[1].x = static_cast<std::int32_t>(width);
	blitData.srcOffsets[1].y = static_cast<std::int32_t>(height);
	blitData.srcOffsets[1].z = 1;

	auto& window = _windowList.GetWindowSimplifier(windowID);

	blitData.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	blitData.dstSubresource.mipLevel = 0;
	blitData.dstSubresource.baseArrayLayer = 0;
	blitData.dstSubresource.layerCount = 1;

	blitData.dstOffsets[0].x = 0;
	blitData.dstOffsets[0].y = 0;
	blitData.dstOffsets[0].z = 0;
	blitData.dstOffsets[1].x = static_cast<std::int32_t>(window.GetWidth());
	blitData.dstOffsets[1].y = static_cast<std::int32_t>(window.GetHeight());
	blitData.dstOffsets[1].z = 1;

	vkCmdBlitImage(_buffer, _imageList.GetImage(imageID), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, window.GetSwapchainImage(swapchainImageIndex), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1, &blitData, VK_FILTER_LINEAR);
}

SecondaryIRCommandBufferInternal::SecondaryIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
	SecondaryNIRCommandBufferInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
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