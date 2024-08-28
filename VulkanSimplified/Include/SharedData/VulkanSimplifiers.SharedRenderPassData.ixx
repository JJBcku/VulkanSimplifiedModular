export module VulkanSimplifiers.SharedRenderPassData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SharedRenderPassData.Internal;
import VulkanSimplifiers.SharedRenderPassData.Data;

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

private:
	SharedRenderPassDataInternal& _internal;
};