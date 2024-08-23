export module VulkanSimplifiers.SharedDataList.CreationData;

export import VulkanSimplifiers.SharedPipelineData.CreationData;
export import VulkanSimplifiers.SharedDescriptorData.CreationData;

export struct SharedDataListCreationData
{
	SharedPipelineDataCreationInfo sharedPipelineData;
	SharedDescriptorDataCreationInfo sharedDescriptorData;

	SharedDataListCreationData() = default;
};