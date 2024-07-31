export module VulkanSimplifiers.DeviceList.Internal;

import std;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.LogicalDevice.Internal;
import VulkanSimplifiers.DeviceList.Data;

export class DeviceListInternal
{
public:
	DeviceListInternal(size_t logicalDeviceListInitialCapacity);
	~DeviceListInternal();

	DeviceListInternal(const DeviceListInternal&) noexcept = delete;

	DeviceListInternal& operator=(const DeviceListInternal&) noexcept = delete;

private:
	UnsortedList<LogicalDevicePointer> _logicalDeviceList;
};