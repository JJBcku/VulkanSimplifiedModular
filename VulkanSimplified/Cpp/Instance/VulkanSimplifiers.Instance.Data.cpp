module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.Instance.Data;

InstanceInitInfo::InstanceInitInfo()
{
	appVersion = 0;
	padding = 0;
	engineVersion = 0;
	usedVulkanApiVersion = VK_API_VERSION_1_0;
	logicalDeviceListInitialCapacity = 0;
}