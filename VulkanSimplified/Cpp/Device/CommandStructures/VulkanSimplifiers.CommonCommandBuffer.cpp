module VulkanSimplifiers.CommonCommandBuffer;

CommonCommandBuffer::CommonCommandBuffer(AutoCleanUpCommandBuffer& ref) : _internal(ref)
{
}

CommonCommandBuffer::~CommonCommandBuffer()
{
}

void CommonCommandBuffer::BeginRecording(CommandBufferUsage usage)
{
	_internal.BeginRecording(usage);
}

void CommonCommandBuffer::EndRecording()
{
	_internal.EndRecording();
}

void CommonCommandBuffer::BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID)
{
	_internal.BindGraphicsPipeline(pipelineID);
}

void CommonCommandBuffer::Draw(std::uint32_t vertexCount, std::uint32_t instanceCount, std::uint32_t firstVertex, std::uint32_t firstInstance)
{
	_internal.Draw(vertexCount, instanceCount, firstVertex, firstInstance);
}