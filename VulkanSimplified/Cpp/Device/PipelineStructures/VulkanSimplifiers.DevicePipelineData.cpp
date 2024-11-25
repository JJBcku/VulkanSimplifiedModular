module VulkanSimplifiers.DevicePipelineData;

DevicePipelineDataSimplifier::DevicePipelineDataSimplifier(DevicePipelineDataInternal& ref) : _internal(ref)
{
}

DevicePipelineDataSimplifier::~DevicePipelineDataSimplifier()
{
}

IDObject<AutoCleanupPipelineLayout> DevicePipelineDataSimplifier::AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserve)
{
	return _internal.AddPipelineLayout(creationData, addOnReserve);
}

std::vector<IDObject<AutoCleanupGraphicsPipeline>> DevicePipelineDataSimplifier::AddGraphicPipelines(const std::vector<GraphicPipelineCreationData>& creationDataList,
	size_t addOnReserve)
{
	return _internal.AddGraphicPipelines(creationDataList, addOnReserve);
}
