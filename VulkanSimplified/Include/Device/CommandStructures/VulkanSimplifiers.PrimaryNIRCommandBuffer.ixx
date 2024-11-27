export module VulkanSimplifiers.PrimaryNIRCommandBuffer;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

import VulkanSimplifiers.ImageDataList.Data;
import VulkanSimplifiers.DeviceRenderPassData.Data;
import VulkanSimplifiers.SharedRenderPassData.Data;

import VulkanSimplifiers.WindowList.Data;

export class PrimaryNIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	PrimaryNIRCommandBufferSimplifier(PrimaryNIRCommandBufferInternal& ref);
	~PrimaryNIRCommandBufferSimplifier();

	PrimaryNIRCommandBufferSimplifier& operator=(const PrimaryNIRCommandBufferSimplifier&) noexcept = delete;

	void BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers = false);
	void EndRenderPass();

	void TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);
	void TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);

	void BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<AutoCleanup2DSimpleImage> imageID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, std::uint32_t swapchainImageIndex);

private:
	PrimaryNIRCommandBufferInternal& _internal;
};