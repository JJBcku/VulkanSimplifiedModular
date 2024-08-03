export module VulkanSimplifiers.PhysicalDevice;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.PhysicalDevice.Internal;
import VulkanSimplifiers.PhysicalDevice.Data;

export class PhysicalDeviceSimplifier
{
public:
	PhysicalDeviceSimplifier(PhysicalDeviceInternal& ref);
	~PhysicalDeviceSimplifier();

	PhysicalDeviceSimplifier& operator=(const PhysicalDeviceSimplifier&) noexcept = delete;

	DeviceVulkanPropertiesSimplified GetVulkanPropertiesSimplified() const;

	VulkanDeviceFeatureFlags GetVulkan10Features() const;
	VulkanDeviceFeatureFlags GetVulkan11Features() const;
	VulkanDeviceFeatureFlags GetVulkan12Features() const;
	VulkanDeviceFeatureFlags GetVulkan13Features() const;

private:
	PhysicalDeviceInternal& _internal;
};