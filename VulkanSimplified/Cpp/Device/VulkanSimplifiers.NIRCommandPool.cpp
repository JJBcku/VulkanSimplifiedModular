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

PrimaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<PrimaryNIRCommandBufferInternal> bufferID)
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

SecondaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<SecondaryNIRCommandBufferInternal> bufferID)
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}

const PrimaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<PrimaryNIRCommandBufferInternal> bufferID) const
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

const SecondaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<SecondaryNIRCommandBufferInternal> bufferID) const
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}