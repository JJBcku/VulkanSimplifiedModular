export module VulkanSimplifiers.PrimaryIRCommandBuffer;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

import VulkanSimplifiers.ImageDataList.Data;
import VulkanSimplifiers.DeviceRenderPassData.Data;
import VulkanSimplifiers.SharedRenderPassData.Data;

export class PrimaryIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	PrimaryIRCommandBufferSimplifier(PrimaryIRCommandBufferInternal& ref);
	~PrimaryIRCommandBufferSimplifier();

	PrimaryIRCommandBufferSimplifier& operator=(const PrimaryIRCommandBufferSimplifier&) noexcept = delete;

	void BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers = false);
	void EndRenderPass();

private:
	PrimaryIRCommandBufferInternal& _internal;
};