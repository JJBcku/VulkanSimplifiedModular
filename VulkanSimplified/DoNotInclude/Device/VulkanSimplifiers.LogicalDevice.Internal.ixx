module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.LogicalDevice.Internal;

import VulkanSimplifiers.LogicalDevice.Data;

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
	LogicalDeviceInternal(const LogicalDeviceInitData& initData);
	~LogicalDeviceInternal();

	LogicalDeviceInternal(const LogicalDeviceInternal&) noexcept = delete;

private:
	VkDevice _logicalDevice;
	VkPhysicalDevice _physicalDevice;
	std::string _physicalDeviceName;
	std::string _logicalDeviceName;
	std::uint32_t _apiVersion;
	std::uint32_t _padding;
	std::vector<VkQueue> _queues;

	bool GetProtectedFlagsValue(QueueCreationFlags queueFlags);

	VkPhysicalDeviceFeatures CompileRequestedVulkan10Features(VulkanDeviceFeatureFlags featureFlags);
	VkPhysicalDeviceVulkan11Features CompileRequestedVulkan11Features(VulkanDeviceFeatureFlags featureFlags);
	VkPhysicalDeviceVulkan12Features CompileRequestedVulkan12Features(VulkanDeviceFeatureFlags featureFlags);
	VkPhysicalDeviceVulkan13Features CompileRequestedVulkan13Features(VulkanDeviceFeatureFlags featureFlags);
};