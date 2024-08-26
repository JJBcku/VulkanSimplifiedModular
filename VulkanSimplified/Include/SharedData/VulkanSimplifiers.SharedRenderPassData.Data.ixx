export module VulkanSimplifiers.SharedRenderPassData.Data;

export struct RenderPassAttachmentData;

export enum class RenderPassAttachmentLoadOP
{
	LOAD = 0x1,
	CLEAR = 0x2,
	DISCARD = 0x3,
};

export enum class RenderPassAttachmentStoreOP
{
	STORE = 0x1,
	DISCARD = 0x2,
};
