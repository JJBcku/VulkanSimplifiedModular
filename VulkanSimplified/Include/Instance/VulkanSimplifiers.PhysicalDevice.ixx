export module VulkanSimplifiers.PhysicalDevice;

import std;
import VulkanSimplifiers.PhysicalDevice.Internal;

export class PhysicalDeviceSimplifier
{
public:
	PhysicalDeviceSimplifier(PhysicalDeviceInternal& ref);
	~PhysicalDeviceSimplifier();

	PhysicalDeviceSimplifier& operator=(const PhysicalDeviceSimplifier&) noexcept = delete;

private:
	PhysicalDeviceInternal& _internal;
};