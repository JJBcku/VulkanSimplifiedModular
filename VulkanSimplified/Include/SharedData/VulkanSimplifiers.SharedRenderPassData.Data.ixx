export module VulkanSimplifiers.SharedRenderPassData.Data;

import std;

export struct RenderPassAttachmentData;
export struct RenderPassAttachmentReference;
export struct SubpassDependencyData;

export constexpr std::uint32_t externalSubpass = std::numeric_limits<std::uint32_t>::max();

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
