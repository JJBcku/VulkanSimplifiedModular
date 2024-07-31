export module VulkanSimplifiers.DeviceList;

import std;
import VulkanSimplifiers.DeviceList.Internal;

export class DeviceListSimplifier
{
public:
	DeviceListSimplifier(DeviceListInternal& ref);
	~DeviceListSimplifier();

	DeviceListSimplifier& operator=(const DeviceListSimplifier&) noexcept = delete;

	size_t GetPhysicalDeviceListSize() const;

private:
	DeviceListInternal& _internal;
};