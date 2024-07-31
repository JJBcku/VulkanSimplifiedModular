export module VulkanSimplifiers.DeviceList;

import std;
import VulkanSimplifiers.DeviceList.Internal;
import VulkanSimplifiers.PhysicalDevice.Internal;
import VulkanSimplifiers.PhysicalDevice;

export class DeviceListSimplifier
{
public:
	DeviceListSimplifier(DeviceListInternal& ref);
	~DeviceListSimplifier();

	DeviceListSimplifier& operator=(const DeviceListSimplifier&) noexcept = delete;

	size_t GetPhysicalDeviceListSize() const;

	PhysicalDeviceSimplifier GetPhysicalDeviceSimplifier(size_t deviceIndex);

private:
	DeviceListInternal& _internal;
};