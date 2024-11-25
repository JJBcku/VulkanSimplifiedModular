export module VulkanSimplifiers.PrimaryNIRCommandBuffer;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

import VulkanSimplifiers.ImageDataList.Data;
import VulkanSimplifiers.DeviceRenderPassData.Data;
import VulkanSimplifiers.SharedRenderPassData.Data;
import VulkanSimplifiers.DevicePipelineData.Data;

export class PrimaryNIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	PrimaryNIRCommandBufferSimplifier(PrimaryNIRCommandBufferInternal& ref);
	~PrimaryNIRCommandBufferSimplifier();

	PrimaryNIRCommandBufferSimplifier& operator=(const PrimaryNIRCommandBufferSimplifier&) noexcept = delete;

	void BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers = false);
	void EndRenderPass();

private:
	PrimaryNIRCommandBufferInternal& _internal;
};