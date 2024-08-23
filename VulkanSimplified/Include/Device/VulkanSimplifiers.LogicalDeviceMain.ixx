export module VulkanSimplifiers.LogicalDeviceMain;

import VulkanSimplifiers.LogicalDeviceMain.Internal;

import VulkanSimplifiers.LogicalDeviceCore.Internal;
import VulkanSimplifiers.ShaderList.Internal;

import VulkanSimplifiers.LogicalDeviceCore;
import VulkanSimplifiers.ShaderList;
import VulkanSimplifiers.DeviceDescriptorData;

export class LogicalDeviceMainSimplifier
{
public:
	LogicalDeviceMainSimplifier(LogicalDeviceMainInternal& ref);
	~LogicalDeviceMainSimplifier();

	LogicalDeviceMainSimplifier& operator=(const LogicalDeviceMainSimplifier&) noexcept = delete;

	LogicalDeviceCoreSimplifier GetLogicalDeviceCoreSimplifier();
	ShaderListSimplifier GetShaderListSimplifier();
	DeviceDescriptorDataSimpifier GetDeviceDescriptorDataSimplifier();

	const LogicalDeviceCoreSimplifier GetLogicalDeviceCoreSimplifier() const;
	const ShaderListSimplifier GetShaderListSimplifier() const;
	const DeviceDescriptorDataSimpifier GetDeviceDescriptorDataSimplifier() const;

private:
	LogicalDeviceMainInternal& _internal;
};