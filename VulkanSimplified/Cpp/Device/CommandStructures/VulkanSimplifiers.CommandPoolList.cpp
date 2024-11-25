module VulkanSimplifiers.CommandPoolList;

CommandPoolListSimplifier::CommandPoolListSimplifier(CommandPoolListInternal& ref) : _internal(ref)
{
}

CommandPoolListSimplifier::~CommandPoolListSimplifier()
{
}

IDObject<std::unique_ptr<NIRCommandPoolInternal>> CommandPoolListSimplifier::AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	return _internal.AddCommandPoolWithoutIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserve);
}

IDObject<std::unique_ptr<IRCommandPoolInternal>> CommandPoolListSimplifier::AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	return _internal.AddCommandPoolWithIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserve);
}

NIRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID)
{
	return _internal.GetCommandPoolWithoutIndividualResetSimplifier(poolID);
}

IRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID)
{
	return _internal.GetCommandPoolWithIndividualResetSimplifier(poolID);
}

const NIRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID) const
{
	return _internal.GetCommandPoolWithoutIndividualResetSimplifier(poolID);
}

const IRCommandPoolSimplifier CommandPoolListSimplifier::GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID) const
{
	return _internal.GetCommandPoolWithIndividualResetSimplifier(poolID);
}