export module VulkanSimplifiers.PhysicalDevice;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.PhysicalDevice.Internal;
import VulkanSimplifiers.PhysicalDevice.Data;
import VulkanSimplifiers.WindowList.Data;

import VulkanSimplifiers.Common.DeviceFeatureFlags;
import VulkanSimplifiers.Common.MemoryData;

export class PhysicalDeviceSimplifier
{
public:
	PhysicalDeviceSimplifier(PhysicalDeviceInternal& ref);
	~PhysicalDeviceSimplifier();

	PhysicalDeviceSimplifier& operator=(const PhysicalDeviceSimplifier&) noexcept = delete;

	DeviceVulkanPropertiesSimplified GetVulkanPropertiesSimplified() const;

	VulkanDeviceFeatureFlags GetVulkan10Features() const;

	SurfaceSupportData GetSurfaceSupport(IDObject<WindowPointer> windowID) const;

	MemoryHeapList GetDeviceMemoryData() const;

private:
	PhysicalDeviceInternal& _internal;
};