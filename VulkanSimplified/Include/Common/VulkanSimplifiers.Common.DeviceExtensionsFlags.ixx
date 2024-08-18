export module VulkanSimplifiers.Common.DeviceExtensionsFlags;

import std;

export typedef std::uint64_t DeviceExtensionFlags;

export enum DeviceKHRExtensionFlagBits : DeviceExtensionFlags
{
	DEVICE_KHR_EXTENSION_SWAPCHAIN = 0x1,
};

export struct DeviceExtensionList
{
	DeviceExtensionFlags khrExtensions;

	DeviceExtensionList();
};