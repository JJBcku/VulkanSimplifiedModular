module VulkanSimplifiers.SharedPipelineData.CreationData;

SharedPipelineDataCreationInfo::SharedPipelineDataCreationInfo()
{
	initialSpecializationElementsCapacity = 0;
	initialShaderPipelineInfoCapacity = 0;

	initialVertexBindingInfoCapacity = 0;
	initialVertexAttributeInfoCapacity = 0;
	initialVertexInputPipelineInfoCapacity = 0;

	initialPipelineInputAssemblyInfoCapacity = 0;
	initialPipelineRasterizationInfoCapacity = 0;
	initialPipelineMultisampleInfoCapacity = 0;
}