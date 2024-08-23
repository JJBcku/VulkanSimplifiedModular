module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DeviceList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.LogicalDeviceMain.Internal;
import VulkanSimplifiers.LogicalDeviceMain.CreationData;

import VulkanSimplifiers.DeviceList.Data;
import VulkanSimplifiers.PhysicalDevice.Internal;
import VulkanSimplifiers.LogicalDeviceCore.CreationData;

import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.SharedDataList.Internal;

export class DeviceListInternal
{
public:
	DeviceListInternal(VkInstance instance, size_t logicalDeviceListInitialCapacity, std::uint32_t instanceVulkanVersion, WindowListInternal& windowList,
		const SharedDataListInternal& sharedDataList);
	~DeviceListInternal();

	DeviceListInternal(const DeviceListInternal&) noexcept = delete;

	DeviceListInternal& operator=(const DeviceListInternal&) noexcept = delete;

	void EnumeratePhysicalDevices();

	size_t GetPhysicalDeviceListSize() const;

	PhysicalDeviceInternal& GetPhysicalDeviceSimplifier(size_t deviceIndex);
	LogicalDeviceMainInternal& GetLogicalDeviceMainSimplifier(IDObject<LogicalDevicePointer> deviceID);

	const PhysicalDeviceInternal& GetPhysicalDeviceSimplifier(size_t deviceIndex) const;
	const LogicalDeviceMainInternal& GetLogicalDeviceMainSimplifier(IDObject<LogicalDevicePointer> deviceID) const;

	IDObject<LogicalDevicePointer> AddLogicalDevice(const LogicalDeviceCreationInfo& createInfo, const DeviceMainCreationData& mainCreationData, size_t addOnReserve);

private:
	VkInstance _instance;
	std::vector<PhysicalDeviceInternal> _physicalDeviceList;
	UnsortedList<LogicalDevicePointer> _logicalDeviceList;

	std::uint32_t _instanceVulkanVersion;
	std::uint32_t _padding;

	WindowListInternal& _windowList;
	const SharedDataListInternal& _sharedDataList;
};