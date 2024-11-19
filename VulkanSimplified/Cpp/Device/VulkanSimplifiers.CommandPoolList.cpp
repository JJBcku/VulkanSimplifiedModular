module VulkanSimplifiers.CommandPoolList;

CommandPoolListSimplifier::CommandPoolListSimplifier(CommandPoolListInternal& ref) : _internal(ref)
{
}

CommandPoolListSimplifier::~CommandPoolListSimplifier()
{
}

IDObject<NIRCommandPoolInternal> CommandPoolListSimplifier::AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	return _internal.AddCommandPoolWithoutIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserve);
}

IDObject<IRCommandPoolInternal> CommandPoolListSimplifier::AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	return _internal.AddCommandPoolWithIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserve);
}

NIRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<NIRCommandPoolInternal> poolID)
{
	return _internal.GetCommandPoolWithoutIndividualResetSimplifier(poolID);
}

IRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithIndividualResetSimplifier(IDObject<IRCommandPoolInternal> poolID)
{
	return _internal.GetCommandPoolWithIndividualResetSimplifier(poolID);
}

const NIRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<NIRCommandPoolInternal> poolID) const
{
	return _internal.GetCommandPoolWithoutIndividualResetSimplifier(poolID);
}

const IRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithIndividualResetSimplifier(IDObject<IRCommandPoolInternal> poolID) const
{
	return _internal.GetCommandPoolWithIndividualResetSimplifier(poolID);
}