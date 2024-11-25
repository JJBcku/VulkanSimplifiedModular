module VulkanSimplifiers.SecondaryNIRCommandBuffer;

SecondaryNIRCommandBufferSimplifier::SecondaryNIRCommandBufferSimplifier(SecondaryNIRCommandBufferInternal& ref) : CommonCommandBuffer(ref), _internal(ref)
{
}

SecondaryNIRCommandBufferSimplifier::~SecondaryNIRCommandBufferSimplifier()
{
}