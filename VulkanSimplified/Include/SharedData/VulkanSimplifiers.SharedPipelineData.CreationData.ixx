export module VulkanSimplifiers.SharedPipelineData.CreationData;

export struct SharedPipelineDataCreationInfo
{
	size_t initialSpecializationElementsCapacity;
	size_t initialShaderPipelineInfoCapacity;
	size_t initialVertexBindingInfoCapacity;
	size_t initialVertexAttributeInfoCapacity;
	size_t initialVertexInputPipelineInfoCapacity;

	SharedPipelineDataCreationInfo();
};