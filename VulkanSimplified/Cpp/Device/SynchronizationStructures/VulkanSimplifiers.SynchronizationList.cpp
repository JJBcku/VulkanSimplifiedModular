module VulkanSimplifiers.SynchronizationList;

SynchronizationListSimplifier::SynchronizationListSimplifier(SynchronizationListInternal& ref) : _internal(ref)
{
}

SynchronizationListSimplifier::~SynchronizationListSimplifier()
{
}

IDObject<AutoCleanupFence> SynchronizationListSimplifier::AddFence(bool createSignaled, size_t addOnReserve)
{
	return _internal.AddFence(createSignaled, addOnReserve);
}

bool SynchronizationListSimplifier::WaitOnFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs, bool waitForAll, std::uint64_t timeout)
{
	return _internal.WaitOnFences(fenceIDs, waitForAll, timeout);
}

void SynchronizationListSimplifier::ResetFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs)
{
	_internal.ResetFences(fenceIDs);
}