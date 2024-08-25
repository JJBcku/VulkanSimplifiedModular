module VulkanSimplifiers.SharedPipelineData.CreationData;

SharedPipelineDataCreationInfo::SharedPipelineDataCreationInfo()
{
	initialSpecializationElementsCapacity = 0;
	initialShaderPipelineInfoCapacity = 0;

	initialVertexBindingInfoCapacity = 0;
	initialVertexAttributeInfoCapacity = 0;
	initialVertexInputPipelineInfoCapacity = 0;

	initialPipelineViewportDataCapacity = 0;
	initialPipelineScissorDataCapacity = 0;

	initialPipelineInputAssemblyInfoCapacity = 0;
	initialPipelineRasterizationInfoCapacity = 0;
	initialPipelineMultisampleInfoCapacity = 0;
	initialPipelineDepthStencilInfoCapacity = 0;
	initialPipelineColorBlendAttachmentInfoCapacity = 0;

	initialPushConstantDataCapacity = 0;
}