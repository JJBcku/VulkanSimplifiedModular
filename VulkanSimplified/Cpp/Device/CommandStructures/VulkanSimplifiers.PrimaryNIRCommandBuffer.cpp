module VulkanSimplifiers.PrimaryNIRCommandBuffer;

PrimaryNIRCommandBufferSimplifier::PrimaryNIRCommandBufferSimplifier(PrimaryNIRCommandBufferInternal& ref) : CommonCommandBuffer(ref), _internal(ref)
{
}

PrimaryNIRCommandBufferSimplifier::~PrimaryNIRCommandBufferSimplifier()
{
}