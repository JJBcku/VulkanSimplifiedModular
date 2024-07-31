export module VulkanSimplifiers.LogicalDevice;

import VulkanSimplifiers.LogicalDevice.Internal;

export class LogicalDeviceSimplifier
{
public:
	LogicalDeviceSimplifier(LogicalDeviceInternal& ref);
	~LogicalDeviceSimplifier();

	LogicalDeviceSimplifier& operator=(const LogicalDeviceSimplifier&) noexcept = delete;

private:
	LogicalDeviceInternal& _internal;
};