module VulkanSimplifiers.NIRCommandPool;

NIRCommandPoolSimplifier::NIRCommandPoolSimplifier(NIRCommandPoolInternal& ref) : _internal(ref)
{
}

NIRCommandPoolSimplifier::~NIRCommandPoolSimplifier()
{
}

std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> NIRCommandPoolSimplifier::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocatePrimaryCommandBuffers(buffersToAllocate, addOnReserve);
}

std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> NIRCommandPoolSimplifier::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	return _internal.AllocateSecondaryCommandBuffers(buffersToAllocate, addOnReserve);
}

PrimaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID)
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

SecondaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID)
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}

const PrimaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID) const
{
	return _internal.GetPrimaryCommandBufferSimplifier(bufferID);
}

const SecondaryNIRCommandBufferSimplifier NIRCommandPoolSimplifier::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID) const
{
	return _internal.GetSecondaryCommandBufferSimplifier(bufferID);
}

void NIRCommandPoolSimplifier::ResetCommandPool(bool freeResources)
{
	_internal.ResetCommandPool(freeResources);
}

bool NIRCommandPoolSimplifier::PresentSwapchainToQueue(IDObject<WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs, std::uint32_t imageIndex)
{
	return _internal.PresentSwapchainToQueue(windowID, waitSemaphoreIDs, imageIndex);
}