module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.PhysicalDevice.Internal;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.PhysicalDevice.Data;
import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.WindowList.Data;

struct QueueSupportSavedData
{
	VkSurfaceKHR surface;
	SurfaceSupportData queueData;

	QueueSupportSavedData();
	QueueSupportSavedData(VkSurfaceKHR initSurface, const SurfaceSupportData& initQueueData);
};

export class PhysicalDeviceInternal
{
public:
	PhysicalDeviceInternal(VkPhysicalDevice physicalDevice, std::uint32_t instanceVulkanVersion, WindowListInternal& windowList);
	~PhysicalDeviceInternal();

	PhysicalDeviceInternal(const PhysicalDeviceInternal&) noexcept = default;

	PhysicalDeviceInternal& operator=(const PhysicalDeviceInternal&) noexcept = delete;

	DeviceVulkanPropertiesSimplified GetVulkanPropertiesSimplified() const;

	VulkanDeviceFeatureFlags GetVulkan10Features() const;
	VulkanDeviceFeatureFlags GetVulkan11Features() const;
	VulkanDeviceFeatureFlags GetVulkan12Features() const;
	VulkanDeviceFeatureFlags GetVulkan13Features() const;

	VkPhysicalDevice GetPhysicalDevice() const;

	SurfaceSupportData GetSurfaceSupport(IDObject<WindowPointer> windowID);

private:
	VkPhysicalDevice _physicalDevice;
	DeviceVulkanPropertiesSimplified _vulkanProperties;

	VulkanDeviceFeatureFlags _device10features;
	VulkanDeviceFeatureFlags _device11features;
	VulkanDeviceFeatureFlags _device12features;
	VulkanDeviceFeatureFlags _device13features;

	WindowListInternal& _windowList;

	DeviceType GetDeviceType(const VkPhysicalDeviceType& deviceType) const;

	Vulkan10DeviceLimits CompileVulkan10DeviceLimits(const VkPhysicalDeviceLimits& deviceLimits) const;

	VulkanDeviceFeatureFlags CompileVulkan10DeviceFeatures(const VkPhysicalDeviceFeatures& deviceFeatures) const;
	VulkanDeviceFeatureFlags CompileVulkan11DeviceFeatures(const VkPhysicalDeviceVulkan11Features& deviceFeatures) const;
	VulkanDeviceFeatureFlags CompileVulkan12DeviceFeatures(const VkPhysicalDeviceVulkan12Features& deviceFeatures) const;
	VulkanDeviceFeatureFlags CompileVulkan13DeviceFeatures(const VkPhysicalDeviceVulkan13Features& deviceFeatures) const;

	DeviceExtensionFlags CompileKHRDeviceExtensionList(const std::vector<VkExtensionProperties>& availableExtensions) const;
};