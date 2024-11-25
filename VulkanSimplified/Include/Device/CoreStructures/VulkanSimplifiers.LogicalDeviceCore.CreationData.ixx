export module VulkanSimplifiers.LogicalDeviceCore.CreationData;

import std;

export import VulkanSimplifiers.Common.DeviceExtensionsFlags;
export import VulkanSimplifiers.Common.DeviceFeatureFlags;

export struct QueueCreateInfo
{
	std::uint32_t queueFamily;
	float queuePriority;

	QueueCreateInfo();
};

export struct LogicalDeviceCreationInfo
{
	size_t physicalGPUIndex;
	std::vector<QueueCreateInfo> queuesCreateInfo;

	VulkanDeviceFeatureFlags vulkan10Features;

	std::string logicalDeviceName;

	DeviceExtensionList requestedExtensions;

	LogicalDeviceCreationInfo();
};