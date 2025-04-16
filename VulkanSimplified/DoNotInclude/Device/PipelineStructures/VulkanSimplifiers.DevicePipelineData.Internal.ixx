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
import VulkanSimplifiers.ShaderList.Internal;
import VulkanSimplifiers.DeviceRenderPassData.Internal;

import VulkanSimplifiers.DevicePipelineData.LayoutCreationData;
import VulkanSimplifiers.DevicePipelineData.GraphicPipelineCreationData;

export class DevicePipelineDataInternal
{
public:
	DevicePipelineDataInternal(const DevicePipelineDataCreationData& creationInfo, const SharedPipelineDataInternal& pipelineData, const DeviceDescriptorDataInternal& descriptorData,
		const ShaderListInternal& shaderList, const DeviceRenderPassDataInternal& renderPassList, VkDevice device);
	~DevicePipelineDataInternal();

	DevicePipelineDataInternal& operator=(const DevicePipelineDataInternal&) noexcept = delete;

	IDObject<AutoCleanupPipelineLayout> AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserve);
	std::vector<IDObject<AutoCleanupGraphicsPipeline>> AddGraphicPipelines(const std::vector<GraphicPipelineCreationData>& creationDataList, size_t addOnReserve);

	VkPipelineLayout GetPipelineLayout(IDObject<AutoCleanupPipelineLayout> layoutID) const;
	VkPipeline GetGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID) const;

private:
	const SharedPipelineDataInternal& _pipelineData;
	const DeviceDescriptorDataInternal& _descriptorData;
	const ShaderListInternal& _shaderList;
	const DeviceRenderPassDataInternal& _renderPassList;

	VkDevice _device;

	UnsortedList<AutoCleanupPipelineLayout> _pipelineLayouts;
	UnsortedList<AutoCleanupGraphicsPipeline> _graphicPipelines;
};