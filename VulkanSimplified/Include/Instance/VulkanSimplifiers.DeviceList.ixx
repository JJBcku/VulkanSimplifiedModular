export module VulkanSimplifiers.DeviceList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.DeviceList.Internal;
import VulkanSimplifiers.PhysicalDevice.Internal;
import VulkanSimplifiers.PhysicalDevice;
import VulkanSimplifiers.DeviceList.Data;
import VulkanSimplifiers.LogicalDeviceMain;
import VulkanSimplifiers.LogicalDeviceMain.Internal;
import VulkanSimplifiers.LogicalDeviceMain.CreationData;
import VulkanSimplifiers.LogicalDeviceCore.CreationData;

export class DeviceListSimplifier
{
public:
	DeviceListSimplifier(DeviceListInternal& ref);
	~DeviceListSimplifier();

	DeviceListSimplifier& operator=(const DeviceListSimplifier&) noexcept = delete;

	size_t GetPhysicalDeviceListSize() const;

	PhysicalDeviceSimplifier GetPhysicalDeviceSimplifier(size_t deviceIndex);
	LogicalDeviceMainSimplifier GetLogicalDeviceMainSimplifier(IDObject<LogicalDevicePointer> deviceID);

	IDObject<LogicalDevicePointer> AddLogicalDevice(const LogicalDeviceCreationInfo& createInfo, const DeviceMainCreationData& mainCreationData, size_t addOnReserve = 0);

private:
	DeviceListInternal& _internal;
};