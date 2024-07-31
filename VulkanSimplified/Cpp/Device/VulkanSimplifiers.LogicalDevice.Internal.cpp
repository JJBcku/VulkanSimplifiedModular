module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.LogicalDevice.Internal;

LogicalDeviceInternal::LogicalDeviceInternal()
{
	_logicalDevice = VK_NULL_HANDLE;
}

LogicalDeviceInternal::~LogicalDeviceInternal()
{
	if (_logicalDevice != VK_NULL_HANDLE)
		vkDestroyDevice(_logicalDevice, nullptr);
}
