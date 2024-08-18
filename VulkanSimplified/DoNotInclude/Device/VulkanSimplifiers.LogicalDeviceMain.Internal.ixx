export module VulkanSimplifiers.LogicalDeviceMain.Internal;

import std;
import VulkanSimplifiers.LogicalDeviceMain.CreationData;
import VulkanSimplifiers.LogicalDeviceCore.InternalData;

import VulkanSimplifiers.LogicalDeviceCore.Internal;
import VulkanSimplifiers.ShaderList.Internal;

import VulkanSimplifiers.WindowList.Internal;

export class LogicalDeviceMainInternal
{
public:
	LogicalDeviceMainInternal(const LogicalDeviceInitData& initData, const DeviceMainCreationData& mainCreationData, WindowListInternal& windowList);
	~LogicalDeviceMainInternal();

	LogicalDeviceMainInternal(const LogicalDeviceMainInternal&) noexcept = delete;

	LogicalDeviceMainInternal& operator=(const LogicalDeviceMainInternal&) noexcept = delete;

	LogicalDeviceCoreInternal& GetLogicalDeviceCoreSimplifier();
	ShaderListInternal& GetShaderListSimplifier();

	const LogicalDeviceCoreInternal& GetLogicalDeviceCoreSimplifier() const;
	const ShaderListInternal& GetShaderListSimplifier() const;

private:
	WindowListInternal& _windowList;

	LogicalDeviceCoreInternal _core;
	ShaderListInternal _shaderList;
};