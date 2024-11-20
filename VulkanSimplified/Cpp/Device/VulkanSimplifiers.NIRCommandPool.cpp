module VulkanSimplifiers.NIRCommandPool;

NIRCommandPoolSimplifier::NIRCommandPoolSimplifier(NIRCommandPoolInternal& ref) : _internal(ref)
{
}

NIRCommandPoolSimplifier::~NIRCommandPoolSimplifier()
{
}

std::vector<IDObject<PrimaryNIRCommandBufferInternal>> NIRCommandPoolSimplifier::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocatePrimaryCommandBuffers(buffersToAllocate, addOnReserve);
}

std::vector<IDObject<SecondaryNIRCommandBufferInternal>> NIRCommandPoolSimplifier::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocateSecondaryCommandBuffers(buffersToAllocate, addOnReserve);
}