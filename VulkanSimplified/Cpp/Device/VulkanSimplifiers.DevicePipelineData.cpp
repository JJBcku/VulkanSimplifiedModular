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
