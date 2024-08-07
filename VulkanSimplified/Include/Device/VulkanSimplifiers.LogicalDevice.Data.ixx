export module VulkanSimplifiers.LogicalDevice.Data;

import std;

export import VulkanSimplifiers.PhysicalDevice.Data;

export typedef std::uint64_t QueueCreationFlags;

export enum QueueCreationFlagBits : QueueCreationFlags
{
	QUEUE_CREATION_CREATE_PROTECTED = 0x1,
};

export struct QueueCreateInfo
{
	std::uint32_t queueFamily;
	float queuePriority;
	QueueCreationFlags queueCreationFlags;

	QueueCreateInfo();
};

export struct LogicalDeviceCreationInfo
{
	size_t physicalGPUIndex;
	std::vector<QueueCreateInfo> queuesCreateInfo;

	VulkanDeviceFeatureFlags vulkan10Features;
	VulkanDeviceFeatureFlags vulkan11Features;
	VulkanDeviceFeatureFlags vulkan12Features;
	VulkanDeviceFeatureFlags vulkan13Features;

	std::string logicalDeviceName;

	LogicalDeviceCreationInfo();
};