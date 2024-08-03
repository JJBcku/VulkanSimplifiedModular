export module VulkanData.InstanceDependent;

import std;
export import ListTemplates.IDObject;
import VulkanSimplifiers.DeviceList.Data;
import VulkanSimplifiers.LogicalDevice.Data;

export struct VulkanDataInstanceDependent
{
	IDObject<LogicalDevicePointer> deviceID;
	size_t graphicsQueue;
	std::optional<size_t> transferQueue;

	VulkanDataInstanceDependent() = default;
};