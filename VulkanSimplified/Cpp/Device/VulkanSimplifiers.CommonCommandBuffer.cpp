module VulkanSimplifiers.CommonCommandBuffer;

CommonCommandBuffer::CommonCommandBuffer(AutoCleanUpCommandBuffer& ref) : _internal(ref)
{
}

CommonCommandBuffer::~CommonCommandBuffer()
{
}