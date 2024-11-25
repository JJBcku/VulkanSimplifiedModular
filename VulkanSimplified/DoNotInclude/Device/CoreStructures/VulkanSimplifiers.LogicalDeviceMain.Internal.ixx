export module VulkanSimplifiers.LogicalDeviceMain.Internal;

import std;
import VulkanSimplifiers.LogicalDeviceMain.CreationData;
import VulkanSimplifiers.LogicalDeviceCore.InternalData;
import VulkanSimplifiers.LogicalDeviceCore.Internal;

import VulkanSimplifiers.PhysicalDevice.Internal;

import VulkanSimplifiers.ShaderList.Internal;
import VulkanSimplifiers.DeviceDescriptorData.Internal;
import VulkanSimplifiers.DevicePipelineData.Internal;
import VulkanSimplifiers.DeviceRenderPassData.Internal;
import VulkanSimplifiers.MemoryObjectsList.Internal;
import VulkanSimplifiers.ImageDataList.Internal;
import VulkanSimplifiers.SynchronizationList.Internal;
import VulkanSimplifiers.CommandPoolList.Internal;

import VulkanSimplifiers.WindowList.Internal;

import VulkanSimplifiers.SharedDataList.Internal;
import VulkanSimplifiers.SharedDescriptorData.Internal;

export class LogicalDeviceMainInternal
{
public:
	LogicalDeviceMainInternal(const LogicalDeviceInitData& initData, const PhysicalDeviceInternal& physicalDevice, const DeviceMainCreationData& mainCreationData,
		WindowListInternal& windowList, const SharedDataListInternal& sharedDataList);
	~LogicalDeviceMainInternal();

	LogicalDeviceMainInternal(const LogicalDeviceMainInternal&) noexcept = delete;

	LogicalDeviceMainInternal& operator=(const LogicalDeviceMainInternal&) noexcept = delete;

	LogicalDeviceCoreInternal& GetLogicalDeviceCoreSimplifier();
	ShaderListInternal& GetShaderListSimplifier();
	DeviceDescriptorDataInternal& GetDeviceDescriptorDataSimplifier();
	DeviceRenderPassDataInternal& GetRenderPassListSimplifier();
	DevicePipelineDataInternal& GetDevicePipelineDataSimplifier();

	MemoryObjectsListInternal& GetMemoryObjectsListSimplifier();
	ImageDataListInternal& GetImageDataListSimplifier();

	SynchronizationListInternal& GetSynchronizationListSimplifier();

	CommandPoolListInternal& GetCommandPoolListSimplifier();

	const LogicalDeviceCoreInternal& GetLogicalDeviceCoreSimplifier() const;
	const ShaderListInternal& GetShaderListSimplifier() const;
	const DeviceDescriptorDataInternal& GetDeviceDescriptorDataSimplifier() const;
	const DeviceRenderPassDataInternal& GetRenderPassListSimplifier() const;
	const DevicePipelineDataInternal& GetDevicePipelineDataSimplifier() const;

	const MemoryObjectsListInternal& GetMemoryObjectsListSimplifier() const;
	const ImageDataListInternal& GetImageDataListSimplifier() const;

	const SynchronizationListInternal& GetSynchronizationListSimplifier() const;

	const CommandPoolListInternal& GetCommandPoolListSimplifier() const;

private:
	LogicalDeviceCoreInternal _core;
	ShaderListInternal _shaderList;
	DeviceDescriptorDataInternal _descriptorList;
	DeviceRenderPassDataInternal _renderPassList;
	DevicePipelineDataInternal _pipelineDataList;

	MemoryObjectsListInternal _memoryList;
	ImageDataListInternal _imageList;

	SynchronizationListInternal _synchronizationList;

	CommandPoolListInternal _commandPoolList;
};