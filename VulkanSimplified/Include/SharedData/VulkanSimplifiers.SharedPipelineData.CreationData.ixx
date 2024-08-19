export module VulkanSimplifiers.SharedPipelineData.CreationData;

export struct SharedPipelineDataCreationInfo
{
	size_t initialSpecializationElementsCapacity;
	size_t initialShaderPipelineInfoCapacity;

	SharedPipelineDataCreationInfo();
};