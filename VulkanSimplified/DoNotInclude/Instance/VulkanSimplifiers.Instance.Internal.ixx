module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Instance.Internal;

import std;

import VulkanSimplifiers.Instance.Data;
import VulkanSimplifiers.DebugCallback;
import VulkanSimplifiers.DeviceList.Internal;

import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.SharedDataList.Internal;

export class InstanceInternal
{
public:
	InstanceInternal(const InstanceInitInfo& initInfo, WindowListInternal& windowList, const SharedDataListInternal& sharedDataList);
	~InstanceInternal();

	InstanceInternal(const InstanceInternal&) noexcept = delete;

	InstanceInternal& operator=(const InstanceInternal&) noexcept = delete;

	VkInstance GetInstance() const;

	DeviceListInternal& GetDeviceListSimplifier();

	const DeviceListInternal& GetDeviceListSimplifier() const;

private:
	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debugMessenger;
	std::optional<DeviceListInternal> _deviceList;
};