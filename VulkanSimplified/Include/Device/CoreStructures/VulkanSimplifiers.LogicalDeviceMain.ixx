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

import VulkanSimplifiers.SynchronizationList;
import VulkanSimplifiers.SynchronizationList.Internal;

import VulkanSimplifiers.CommandPoolList;

import VulkanSimplifiers.MemoryObjectsList;
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

	MemoryObjectsListSimplifier GetMemoryObjectsListSimplifier();
	ImageDataListSimplifier GetImageDataListSimplifier();

	SynchronizationListSimplifier GetSynchronizationListSimplifier();

	CommandPoolListSimplifier GetCommandPoolListSimplifier();

	const LogicalDeviceCoreSimplifier GetLogicalDeviceCoreSimplifier() const;
	const ShaderListSimplifier GetShaderListSimplifier() const;
	const DeviceDescriptorDataSimpifier GetDeviceDescriptorDataSimplifier() const;
	const DeviceRenderPassDataSimplifier GetRenderPassListSimplifier() const;
	const DevicePipelineDataSimplifier GetDevicePipelineDataSimplifier() const;

	const MemoryObjectsListSimplifier GetMemoryObjectsListSimplifier() const;
	const ImageDataListSimplifier GetImageDataListSimplifier() const;

	const SynchronizationListSimplifier GetSynchronizationListSimplifier() const;

	const CommandPoolListSimplifier GetCommandPoolListSimplifier() const;

private:
	LogicalDeviceMainInternal& _internal;
};