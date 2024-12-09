module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Window.InternalData;

import std;

export import VulkanSimplifiers.Window.Data;

export struct SwapchainInitData
{
	VkDevice device;
	VkPhysicalDevice physicalDevice;
	VkPresentModeKHR surfacePresentMode;
	VkFormat format;
	VkSwapchainCreateFlagsKHR flags;
	std::uint32_t imageAmount;
	std::vector<std::uint32_t> queueFamilies;

	SwapchainInitData();
};