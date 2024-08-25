export module VulkanSimplifiers.DevicePipelineData.LayoutCreationData;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.DeviceDescriptorData.Data;
export import VulkanSimplifiers.SharedPipelineData.Data;

export struct PipelineLayoutCreationData
{
	std::vector<IDObject<AutoCleanupDescriptorSetLayout>> _descriptorSets;
	std::vector<IDObject<PushConstantData>> _pushConstants;

	PipelineLayoutCreationData() = default;
};