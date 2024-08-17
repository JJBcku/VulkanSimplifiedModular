export module VulkanSimplifiers.DeviceList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.DeviceList.Internal;
import VulkanSimplifiers.PhysicalDevice.Internal;
import VulkanSimplifiers.PhysicalDevice;
import VulkanSimplifiers.DeviceList.Data;
import VulkanSimplifiers.LogicalDevice.Data;
import VulkanSimplifiers.LogicalDevice;

export class DeviceListSimplifier
{
public:
	DeviceListSimplifier(DeviceListInternal& ref);
	~DeviceListSimplifier();

	DeviceListSimplifier& operator=(const DeviceListSimplifier&) noexcept = delete;

	size_t GetPhysicalDeviceListSize() const;

	PhysicalDeviceSimplifier GetPhysicalDeviceSimplifier(size_t deviceIndex);
	LogicalDeviceSimplifier GetLogicalDeviceSimplifier(IDObject<LogicalDevicePointer> deviceID);

	IDObject<LogicalDevicePointer> AddLogicalDevice(const LogicalDeviceCreationInfo& createInfo, size_t addOnReserve = 0);

private:
	DeviceListInternal& _internal;
};