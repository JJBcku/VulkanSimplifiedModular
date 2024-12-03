module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.LogicalDeviceCore.InternalData;

import std;
export import VulkanSimplifiers.LogicalDeviceCore.CreationData;

export struct LogicalDeviceInitData
{
	VkPhysicalDevice physicalDevice;
	std::string physicalDeviceName;

	LogicalDeviceCreationInfo creationInfo;
	std::uint32_t apiVersion;
	std::uint32_t padding;

	size_t queueFamiliesCount;

	LogicalDeviceInitData();
};