module VulkanSimplifiers.CommandPoolQFGroupList;

CommandPoolQFGroupListSimplifier::CommandPoolQFGroupListSimplifier(CommandPoolQFGroupListInternal& ref) : _internal(ref)
{
}

CommandPoolQFGroupListSimplifier::~CommandPoolQFGroupListSimplifier()
{
}

IDObject<std::unique_ptr<NIRCommandPoolInternal>> CommandPoolQFGroupListSimplifier::AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	return _internal.AddCommandPoolWithoutIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserve);
}

IDObject<std::unique_ptr<IRCommandPoolInternal>> CommandPoolQFGroupListSimplifier::AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	return _internal.AddCommandPoolWithIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserve);
}

NIRCommandPoolSimplifier CommandPoolQFGroupListSimplifier::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID)
{
	return _internal.GetCommandPoolWithoutIndividualResetSimplifier(poolID);
}

IRCommandPoolSimplifier CommandPoolQFGroupListSimplifier::GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID)
{
	return _internal.GetCommandPoolWithIndividualResetSimplifier(poolID);
}

const NIRCommandPoolSimplifier CommandPoolQFGroupListSimplifier::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID) const
{
	return _internal.GetCommandPoolWithoutIndividualResetSimplifier(poolID);
}

const IRCommandPoolSimplifier CommandPoolQFGroupListSimplifier::GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID) const
{
	return _internal.GetCommandPoolWithIndividualResetSimplifier(poolID);
}

void CommandPoolQFGroupListSimplifier::SubmitBuffers(size_t queueID, const std::vector<CommandBufferSubmitInfo>& submitInfos, std::optional<IDObject<AutoCleanupFence>> fenceID)
{
	_internal.SubmitBuffers(queueID, submitInfos, fenceID);
}