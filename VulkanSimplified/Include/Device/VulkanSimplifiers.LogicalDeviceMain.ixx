export module VulkanSimplifiers.LogicalDeviceMain;

import VulkanSimplifiers.LogicalDeviceMain.Internal;

import VulkanSimplifiers.LogicalDeviceCore.Internal;
import VulkanSimplifiers.ShaderList.Internal;
import VulkanSimplifiers.DeviceDescriptorData.Internal;
import VulkanSimplifiers.DeviceRenderPassData.Internal;
import VulkanSimplifiers.DevicePipelineData.Internal;
import VulkanSimplifiers.ImageDataList.Internal;

import VulkanSimplifiers.LogicalDeviceCore;
import VulkanSimplifiers.ShaderList;
import VulkanSimplifiers.DeviceDescriptorData;
import VulkanSimplifiers.DeviceRenderPassData;
import VulkanSimplifiers.DevicePipelineData;
import VulkanSimplifiers.ImageDataList;

export class LogicalDeviceMainSimplifier
{
public:
	LogicalDeviceMainSimplifier(LogicalDeviceMainInternal& ref);
	~LogicalDeviceMainSimplifier();

	LogicalDeviceMainSimplifier& operator=(const LogicalDeviceMainSimplifier&) noexcept = delete;

	LogicalDeviceCoreSimplifier GetLogicalDeviceCoreSimplifier();
	ShaderListSimplifier GetShaderListSimplifier();
	DeviceDescriptorDataSimpifier GetDeviceDescriptorDataSimplifier();
	DeviceRenderPassDataSimplifier GetRenderPassListSimplifier();
	DevicePipelineDataSimplifier GetDevicePipelineDataSimplifier();
	ImageDataListSimplifier GetImageDataListSimplifier();

	const LogicalDeviceCoreSimplifier GetLogicalDeviceCoreSimplifier() const;
	const ShaderListSimplifier GetShaderListSimplifier() const;
	const DeviceDescriptorDataSimpifier GetDeviceDescriptorDataSimplifier() const;
	const DeviceRenderPassDataSimplifier GetRenderPassListSimplifier() const;
	const DevicePipelineDataSimplifier GetDevicePipelineDataSimplifier() const;
	const ImageDataListSimplifier GetImageDataListSimplifier() const;

private:
	LogicalDeviceMainInternal& _internal;
};