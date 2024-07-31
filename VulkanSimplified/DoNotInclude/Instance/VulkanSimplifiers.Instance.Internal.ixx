module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Instance.Internal;

import std;

import VulkanSimplifiers.Instance.Data;
import VulkanSimplifiers.DebugCallback;
import VulkanSimplifiers.DeviceList.Internal;

export class InstanceInternal
{
public:
	InstanceInternal(const InstanceInitInfo& initInfo);
	~InstanceInternal();

	InstanceInternal(const InstanceInternal&) noexcept = delete;

	InstanceInternal& operator=(const InstanceInternal&) noexcept = delete;

private:
	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debugMessenger;
	DeviceListInternal _deviceList;
};