export module VulkanSimplifiers.SharedDataList.CreationData;

export import VulkanSimplifiers.SharedDescriptorData.CreationData;
export import VulkanSimplifiers.SharedPipelineData.CreationData;
export import VulkanSimplifiers.SharedRenderPassData.CreationData;

export struct SharedDataListCreationData
{
	SharedDescriptorDataCreationInfo sharedDescriptorData;
	SharedPipelineDataCreationInfo sharedPipelineData;
	SharedRenderPassDataCreationInfo sharedRenderPassData;

	SharedDataListCreationData() = default;
};