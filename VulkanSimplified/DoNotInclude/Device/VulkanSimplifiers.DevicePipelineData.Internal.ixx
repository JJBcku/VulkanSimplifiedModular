module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DevicePipelineData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.DevicePipelineData.CreationData;
import VulkanSimplifiers.DevicePipelineData.InternalData;
import VulkanSimplifiers.DevicePipelineData.LayoutCreationData;

import VulkanSimplifiers.SharedPipelineData.Internal;
import VulkanSimplifiers.DeviceDescriptorData.Internal;

import VulkanSimplifiers.DevicePipelineData.LayoutCreationData;

export class DevicePipelineDataInternal
{
public:
	DevicePipelineDataInternal(const DevicePipelineDataCreationData& creationInfo, const SharedPipelineDataInternal& pipelineData, const DeviceDescriptorDataInternal& descriptorData,
		VkDevice device);
	~DevicePipelineDataInternal();

	DevicePipelineDataInternal& operator=(const DevicePipelineDataInternal&) noexcept = delete;

	IDObject<AutoCleanupPipelineLayout> AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserve);

private:
	const SharedPipelineDataInternal& _pipelineData;
	const DeviceDescriptorDataInternal& _descriptorData;
	VkDevice _device;

	UnsortedList<AutoCleanupPipelineLayout> _pipelineLayouts;
};