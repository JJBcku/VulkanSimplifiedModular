module VulkanSimplifiers.SecondaryIRCommandBuffer;

SecondaryIRCommandBufferSimplifier::SecondaryIRCommandBufferSimplifier(SecondaryIRCommandBufferInternal& ref) : CommonCommandBuffer(ref), _internal(ref)
{
}

SecondaryIRCommandBufferSimplifier::~SecondaryIRCommandBufferSimplifier()
{
}