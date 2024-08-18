export module VulkanData.InstanceDependent;

import std;
export import ListTemplates.IDObject;
import VulkanSimplifiers.DeviceList.Data;
import VulkanSimplifiers.LogicalDeviceCore.Data;
import VulkanSimplifiers.Common.DeviceExtensionsFlags;

export struct VulkanDataInstanceDependent
{
	IDObject<LogicalDevicePointer> deviceID;
	size_t graphicsQueue;
	std::optional<size_t> transferQueue;
	size_t presentQueue;

	DeviceExtensionList usedDeviceExtensions;
	Vulkan10DeviceLimits device10Limits;
	FormatsSupportedFullFeatures deviceFormatsSupport;
	SurfaceSupportData surfaceSupport;

	VulkanDataInstanceDependent() = default;
};