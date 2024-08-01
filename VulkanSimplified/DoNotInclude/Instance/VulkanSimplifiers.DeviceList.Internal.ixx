module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DeviceList.Internal;

import std;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.LogicalDevice.Internal;
import VulkanSimplifiers.DeviceList.Data;
import VulkanSimplifiers.PhysicalDevice.Internal;

export class DeviceListInternal
{
public:
	DeviceListInternal(VkInstance instance, size_t logicalDeviceListInitialCapacity, std::uint32_t instanceVulkanVersion);
	~DeviceListInternal();

	DeviceListInternal(const DeviceListInternal&) noexcept = delete;

	DeviceListInternal& operator=(const DeviceListInternal&) noexcept = delete;

	void EnumeratePhysicalDevices();

	size_t GetPhysicalDeviceListSize() const;

	PhysicalDeviceInternal& GetPhysicalDeviceSimplifier(size_t deviceIndex);

	const PhysicalDeviceInternal& GetPhysicalDeviceSimplifier(size_t deviceIndex) const;

private:
	VkInstance _instance;
	std::vector<PhysicalDeviceInternal> _physicalDeviceList;
	UnsortedList<LogicalDevicePointer> _logicalDeviceList;

	std::uint32_t _instanceVulkanVersion;
	std::uint32_t _padding;
};