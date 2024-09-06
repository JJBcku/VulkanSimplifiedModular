module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.Common.ImageLayouts.Internal;

VkImageLayout TranslateImageLayout(ImageLayoutFlags imageLayout)
{
	VkImageLayout ret = VK_IMAGE_LAYOUT_UNDEFINED;

	switch (imageLayout)
	{
	case ImageLayoutFlags::PRESENT:
		ret = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		break;
	case ImageLayoutFlags::TRANSFER_DESTINATION:
		ret = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		break;
	case ImageLayoutFlags::TRANSFER_SOURCE:
		ret = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		break;
	case ImageLayoutFlags::SHADER_READ_ONLY:
		ret = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
		ret = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
		ret = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::COLOR_ATTACHMENT:
		ret = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::GENERAL:
		ret = VK_IMAGE_LAYOUT_GENERAL;
		break;
	case ImageLayoutFlags::UNDEFINED:
	default:
		break;
	}

	return ret;
}