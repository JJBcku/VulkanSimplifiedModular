export module VulkanData.RenderPassData;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedRenderPassData.Data;

export struct VulkanRenderPassData
{
	std::vector<IDObject<RenderPassAttachmentData>> renderPassAttachments;
	IDObject<RenderPassAttachmentReference> colorAttachmentReference;

	VulkanRenderPassData() = default;
};