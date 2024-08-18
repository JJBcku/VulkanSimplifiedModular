export module VulkanSimplifiers.LogicalDeviceMain;

import VulkanSimplifiers.LogicalDeviceMain.Internal;

import VulkanSimplifiers.LogicalDeviceCore.Internal;
import VulkanSimplifiers.ShaderList.Internal;

import VulkanSimplifiers.LogicalDeviceCore;
import VulkanSimplifiers.ShaderList;

export class LogicalDeviceMainSimplifier
{
public:
	LogicalDeviceMainSimplifier(LogicalDeviceMainInternal& ref);
	~LogicalDeviceMainSimplifier();

	LogicalDeviceMainSimplifier& operator=(const LogicalDeviceMainSimplifier&) noexcept = delete;

	LogicalDeviceCoreSimplifier GetLogicalDeviceCoreSimplifier();
	ShaderListSimplifier GetShaderListSimplifier();

private:
	LogicalDeviceMainInternal& _internal;
};