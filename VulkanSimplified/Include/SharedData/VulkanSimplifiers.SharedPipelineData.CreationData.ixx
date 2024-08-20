export module VulkanSimplifiers.SharedPipelineData.CreationData;

export struct SharedPipelineDataCreationInfo
{
	size_t initialSpecializationElementsCapacity;
	size_t initialShaderPipelineInfoCapacity;

	size_t initialVertexBindingInfoCapacity;
	size_t initialVertexAttributeInfoCapacity;
	size_t initialVertexInputPipelineInfoCapacity;

	size_t initialPipelineInputAssemblyInfoCapacity;
	size_t initialPipelineRasterizationInfoCapacity;
	size_t initialPipelineMultisampleInfoCapacity;

	SharedPipelineDataCreationInfo();
};