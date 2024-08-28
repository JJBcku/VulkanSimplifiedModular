module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SharedRenderPassData.InternalData;

RenderPassAttachmentData::RenderPassAttachmentData()
{
	format = VK_FORMAT_UNDEFINED;
	samples = static_cast<VkSampleCountFlagBits>(std::numeric_limits<std::uint32_t>::max());
	loadOP = static_cast<VkAttachmentLoadOp>(std::numeric_limits<std::uint32_t>::max());
	storeOP = static_cast<VkAttachmentStoreOp>(std::numeric_limits<std::uint32_t>::max());
	initialLayout = static_cast<VkImageLayout>(std::numeric_limits<std::uint32_t>::max());
	finalLayout = static_cast<VkImageLayout>(std::numeric_limits<std::uint32_t>::max());
}

RenderPassAttachmentReference::RenderPassAttachmentReference()
{
	attachmentIndex = std::numeric_limits<std::uint32_t>::max();
	attachmentLayout = VK_IMAGE_LAYOUT_MAX_ENUM;
}

SubpassDependencyData::SubpassDependencyData()
{
	srcSubpass = static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max());
	dstSubpass = static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max());
	srcStageFlags = 0;
	dstStageFlags = 0;
	srcAccessFlags = 0;
	dstAccessFlags = 0;
}
