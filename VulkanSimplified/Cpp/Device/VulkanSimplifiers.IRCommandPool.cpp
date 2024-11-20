module VulkanSimplifiers.IRCommandPool;

IRCommandPoolSimplifier::IRCommandPoolSimplifier(IRCommandPoolInternal& ref) : _internal(ref)
{
}

IRCommandPoolSimplifier::~IRCommandPoolSimplifier()
{
}

std::vector<IDObject<PrimaryIRCommandBufferInternal>> IRCommandPoolSimplifier::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocatePrimaryCommandBuffers(buffersToAllocate, addOnReserve);
}

std::vector<IDObject<SecondaryIRCommandBufferInternal>> IRCommandPoolSimplifier::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocateSecondaryCommandBuffers(buffersToAllocate, addOnReserve);
}