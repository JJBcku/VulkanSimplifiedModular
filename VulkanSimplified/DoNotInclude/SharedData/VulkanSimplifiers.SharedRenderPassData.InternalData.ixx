module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedRenderPassData.InternalData;

import std;
export import ListTemplates.IDObject;

export struct RenderPassAttachmentData
{
	VkFormat format;
	VkSampleCountFlagBits samples;
	VkAttachmentLoadOp loadOP;
	VkAttachmentStoreOp storeOP;
	VkImageLayout initialLayout;
	VkImageLayout finalLayout;

	RenderPassAttachmentData();

	bool operator==(const RenderPassAttachmentData&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassAttachmentData&) const noexcept = default;
};

export struct RenderPassAttachmentReference
{
	std::uint32_t attachmentIndex;
	VkImageLayout attachmentLayout;

	RenderPassAttachmentReference();

	bool operator==(const RenderPassAttachmentReference&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassAttachmentReference&) const noexcept = default;
};