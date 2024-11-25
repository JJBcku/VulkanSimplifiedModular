module VulkanSimplifiers.DevicePipelineData.GraphicPipelineCreationData;

GraphicPipelineDerrivationData::GraphicPipelineDerrivationData()
{
	settings = PipelineDerrivationSettings::DO_NOT_DERRIVE;
}

ShaderSpecializationData::ShaderSpecializationData()
{
	dataSize = std::numeric_limits<size_t>::max();
	data = nullptr;
}

GraphicPipelineCreationData::GraphicPipelineCreationData()
{
	subpassIndex = std::numeric_limits<std::uint32_t>::max();
	padding = 0;
}
