export module VulkanSimplifiers.PrimaryIRCommandBuffer;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

import VulkanSimplifiers.ImageDataList.Data;
import VulkanSimplifiers.DeviceRenderPassData.Data;
import VulkanSimplifiers.SharedRenderPassData.Data;

import VulkanSimplifiers.WindowList.Data;

export class PrimaryIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	PrimaryIRCommandBufferSimplifier(PrimaryIRCommandBufferInternal& ref);
	~PrimaryIRCommandBufferSimplifier();

	PrimaryIRCommandBufferSimplifier& operator=(const PrimaryIRCommandBufferSimplifier&) noexcept = delete;

	void BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers = false);
	void EndRenderPass();

	void ResetCommandBuffer(bool freeResources);

	void TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);
	void TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);

	void BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<AutoCleanup2DSimpleImage> imageID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, std::uint32_t swapchainImageIndex);

private:
	PrimaryIRCommandBufferInternal& _internal;
};