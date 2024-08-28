export module VulkanSimplifiers.SharedRenderPassData.Data;

export import VulkanSimplifiers.Common.ImageLayouts;
export import VulkanSimplifiers.Common.DataFormatFlags;
export import VulkanSimplifiers.Common.ImageSampleFlags;

export struct RenderPassAttachmentData;
export struct RenderPassAttachmentReference;

export enum class RenderPassAttachmentLoadOP
{
	LOAD = 0x1,
	CLEAR = 0x2,
	IGNORE = 0x3,
};

export enum class RenderPassAttachmentStoreOP
{
	STORE = 0x1,
	IGNORE = 0x2,
};
