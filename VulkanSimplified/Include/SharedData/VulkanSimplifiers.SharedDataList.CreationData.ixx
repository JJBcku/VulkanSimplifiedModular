export module VulkanSimplifiers.SharedDataList.CreationData;

export import VulkanSimplifiers.SharedPipelineData.CreationData;

export struct SharedDataListCreationData
{
	SharedPipelineDataCreationInfo sharedPipelineData;

	SharedDataListCreationData() = default;
};