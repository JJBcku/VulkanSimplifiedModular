export module VulkanSimplifiers.DeviceList;

import std;
import VulkanSimplifiers.DeviceList.Internal;

export class DeviceListSimplifier
{
public:
	DeviceListSimplifier(DeviceListInternal& ref);
	~DeviceListSimplifier();

	DeviceListSimplifier& operator=(const DeviceListSimplifier&) noexcept = delete;

private:
	DeviceListInternal& _internal;
};