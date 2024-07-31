module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.LogicalDevice.Internal;

export class LogicalDeviceInternal
{
public:
	LogicalDeviceInternal();
	~LogicalDeviceInternal();

private:
	VkDevice _logicalDevice;
};