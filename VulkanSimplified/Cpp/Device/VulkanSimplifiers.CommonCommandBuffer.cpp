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