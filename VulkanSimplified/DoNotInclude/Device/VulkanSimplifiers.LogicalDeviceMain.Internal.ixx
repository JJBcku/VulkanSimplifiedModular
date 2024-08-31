export module VulkanSimplifiers.LogicalDeviceMain.Internal;

import std;
import VulkanSimplifiers.LogicalDeviceMain.CreationData;
import VulkanSimplifiers.LogicalDeviceCore.InternalData;
import VulkanSimplifiers.LogicalDeviceCore.Internal;

import VulkanSimplifiers.ShaderList.Internal;
import VulkanSimplifiers.DeviceDescriptorData.Internal;
import VulkanSimplifiers.DevicePipelineData.Internal;
import VulkanSimplifiers.DeviceRenderPassData.Internal;
import VulkanSimplifiers.ImageDataList.Internal;

import VulkanSimplifiers.WindowList.Internal;

import VulkanSimplifiers.SharedDataList.Internal;
import VulkanSimplifiers.SharedDescriptorData.Internal;

export class LogicalDeviceMainInternal
{
public:
	LogicalDeviceMainInternal(const LogicalDeviceInitData& initData, const DeviceMainCreationData& mainCreationData, WindowListInternal& windowList,
		const SharedDataListInternal& sharedDataList);
	~LogicalDeviceMainInternal();

	LogicalDeviceMainInternal(const LogicalDeviceMainInternal&) noexcept = delete;

	LogicalDeviceMainInternal& operator=(const LogicalDeviceMainInternal&) noexcept = delete;

	LogicalDeviceCoreInternal& GetLogicalDeviceCoreSimplifier();
	ShaderListInternal& GetShaderListSimplifier();
	DeviceDescriptorDataInternal& GetDeviceDescriptorDataSimplifier();
	DeviceRenderPassDataInternal& GetRenderPassListSimplifier();
	DevicePipelineDataInternal& GetDevicePipelineDataSimplifier();
	ImageDataListInternal& GetImageDataListSimplifier();

	const LogicalDeviceCoreInternal& GetLogicalDeviceCoreSimplifier() const;
	const ShaderListInternal& GetShaderListSimplifier() const;
	const DeviceDescriptorDataInternal& GetDeviceDescriptorDataSimplifier() const;
	const DeviceRenderPassDataInternal& GetRenderPassListSimplifier() const;
	const DevicePipelineDataInternal& GetDevicePipelineDataSimplifier() const;
	const ImageDataListInternal& GetImageDataListSimplifier() const;

private:
	LogicalDeviceCoreInternal _core;
	ShaderListInternal _shaderList;
	DeviceDescriptorDataInternal _descriptorList;
	DeviceRenderPassDataInternal _renderPassList;
	DevicePipelineDataInternal _pipelineDataList;
	ImageDataListInternal _imageList;
};