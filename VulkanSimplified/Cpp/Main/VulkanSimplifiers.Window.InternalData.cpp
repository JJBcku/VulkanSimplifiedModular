module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.Window.InternalData;

SwapchainInitData::SwapchainInitData()
{
	device = VK_NULL_HANDLE;
	surfacePresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	format = VK_FORMAT_UNDEFINED;
	flags = 0;
	imageAmount = 0;
}
