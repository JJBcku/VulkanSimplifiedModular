module VulkanSimplifiers.IRCommandPool;

IRCommandPoolSimplifier::IRCommandPoolSimplifier(IRCommandPoolInternal& ref) : _internal(ref)
{
}

IRCommandPoolSimplifier::~IRCommandPoolSimplifier()
{
}

std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> IRCommandPoolSimplifier::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocatePrimaryCommandBuffers(buffersToAllocate, addOnReserve);
}

std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> IRCommandPoolSimplifier::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocateSecondaryCommandBuffers(buffersToAllocate, addOnReserve);
}

PrimaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID)
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

SecondaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID)
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}

const PrimaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID) const
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

const SecondaryIRCommandBufferSimplifier IRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID) const
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}

void IRCommandPoolSimplifier::ResetCommandPool(bool freeResources)
{
	_internal.ResetCommandPool(freeResources);
}