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

PrimaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<PrimaryIRCommandBufferInternal> bufferID)
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

SecondaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<SecondaryIRCommandBufferInternal> bufferID)
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}

const PrimaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<PrimaryIRCommandBufferInternal> bufferID) const
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

const SecondaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<SecondaryIRCommandBufferInternal> bufferID) const
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}