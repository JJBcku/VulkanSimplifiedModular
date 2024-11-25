export module VulkanSimplifiers.SharedRenderPassData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SharedRenderPassData.Internal;
import VulkanSimplifiers.SharedRenderPassData.Data;
import VulkanSimplifiers.SharedRenderPassData.InternalData;

import VulkanSimplifiers.Common.DataFormatFlags;
import VulkanSimplifiers.Common.ImageSampleFlags;
import VulkanSimplifiers.Common.ImageLayouts;
import VulkanSimplifiers.Common.PipelineStageFlags;
import VulkanSimplifiers.Common.AccessFlags;

export class SharedRenderPassDataSimplifier
{
public:
	SharedRenderPassDataSimplifier(SharedRenderPassDataInternal& ref);
	~SharedRenderPassDataSimplifier();

	SharedRenderPassDataSimplifier& operator=(const SharedRenderPassDataSimplifier&) noexcept = delete;

	IDObject<RenderPassAttachmentData> AddRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples, RenderPassAttachmentLoadOP loadOP,
		RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserve = 0);

	IDObject<RenderPassAttachmentReference> AddRenderPassAttachmentReference(std::uint32_t attachmentIndex, ImageLayoutFlags subpassUsedAttachmentLayout, size_t addOnReserve = 0);

	IDObject<SubpassDependencyData> AddSubpassDependency(std::uint32_t srcSubpass, std::uint32_t dstSubpass, PipelineStageFlags srcStageFlags, PipelineStageFlags dstStageFlags,
		AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserve = 0);

	IDObject<RenderPassDoubleColorClearValues> AddDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserve = 0);
	IDObject<RenderPassInt64ColorClearValues> AddInt64ColorClearValue(std::int64_t r, std::int64_t g, std::int64_t b, std::int64_t a, size_t addOnReserve = 0);
	IDObject<RenderPassUInt64ColorClearValues> AddUInt64ColorClearValue(std::uint64_t r, std::uint64_t g, std::uint64_t b, std::uint64_t a, size_t addOnReserve = 0);

	IDObject<RenderPassFloatColorClearValues> AddFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserve = 0);
	IDObject<RenderPassIntColorClearValues> AddIntColorClearValue(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a, size_t addOnReserve = 0);
	IDObject<RenderPassUIntColorClearValues> AddUIntColorClearValue(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a, size_t addOnReserve = 0);

	IDObject<RenderPassDepthStencilClearValues> AddDepthStencilClearValue(float depth, std::uint32_t stencil, size_t addOnReserve = 0);

private:
	SharedRenderPassDataInternal& _internal;
};