module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Window.InternalData;

import std;

export struct SwapchainInitData
{
	VkDevice device;
	VkPresentModeKHR surfacePresentMode;
	VkFormat format;
	VkSwapchainCreateFlagsKHR flags;
	std::uint32_t imageAmount;
	std::vector<std::uint32_t> queueFamilies;

	SwapchainInitData();
};