module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.LogicalDevice.Internal;

export class LogicalDeviceInternal
{
public:
	LogicalDeviceInternal();
	~LogicalDeviceInternal();

	LogicalDeviceInternal(const LogicalDeviceInternal&) noexcept = delete;

private:
	VkDevice _logicalDevice;
};