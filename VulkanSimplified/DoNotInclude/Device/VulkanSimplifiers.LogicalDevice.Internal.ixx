module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.LogicalDevice.Internal;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.LogicalDevice.Data;
import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.WindowList.Data;
import VulkanSimplifiers.Window.InternalData;
import VulkanSimplifiers.Window.Internal;

export struct LogicalDeviceInitData
{
	VkPhysicalDevice physicalDevice;
	std::string physicalDeviceName;

	LogicalDeviceCreationInfo creationInfo;
	std::uint32_t apiVersion;
	std::uint32_t padding;


	LogicalDeviceInitData();
};

export class LogicalDeviceInternal
{
public:
	LogicalDeviceInternal(const LogicalDeviceInitData& initData, WindowListInternal& windowList);
	~LogicalDeviceInternal();

	LogicalDeviceInternal(const LogicalDeviceInternal&) noexcept = delete;

	LogicalDeviceInternal& operator=(const LogicalDeviceInternal&) noexcept = delete;

	void CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected, bool throwOnSwapchainExist, bool throwOnDeviceChange);

private:
	WindowListInternal& _windowList;

	VkDevice _logicalDevice;
	VkPhysicalDevice _physicalDevice;
	std::string _physicalDeviceName;
	std::string _logicalDeviceName;
	std::uint32_t _apiVersion;
	std::uint32_t _padding;
	std::vector<std::pair<VkQueue, std::uint32_t>> _queues;

	bool GetProtectedFlagsValue(QueueCreationFlags queueFlags);

	VkPhysicalDeviceFeatures CompileRequestedVulkan10Features(VulkanDeviceFeatureFlags featureFlags);
	VkPhysicalDeviceVulkan11Features CompileRequestedVulkan11Features(VulkanDeviceFeatureFlags featureFlags);
	VkPhysicalDeviceVulkan12Features CompileRequestedVulkan12Features(VulkanDeviceFeatureFlags featureFlags);
	VkPhysicalDeviceVulkan13Features CompileRequestedVulkan13Features(VulkanDeviceFeatureFlags featureFlags);

	std::vector<const char*> CompileRequestedExtensions(const RequestedExtensionList& deviceExtensionList) const;

	void CompileRequestedKHRExtensions(std::vector<const char*>& requiredExtensions, DeviceExtensionFlags khrExtensions) const;

	VkPresentModeKHR TranslatePresentMode(SurfacePresentModeBits presentMode) const;
};