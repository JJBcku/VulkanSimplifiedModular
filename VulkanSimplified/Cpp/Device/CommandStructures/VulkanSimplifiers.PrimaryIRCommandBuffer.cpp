module VulkanSimplifiers.PrimaryIRCommandBuffer;

PrimaryIRCommandBufferSimplifier::PrimaryIRCommandBufferSimplifier(PrimaryIRCommandBufferInternal& ref) : CommonCommandBuffer(ref), _internal(ref)
{
}

PrimaryIRCommandBufferSimplifier::~PrimaryIRCommandBufferSimplifier()
{
}