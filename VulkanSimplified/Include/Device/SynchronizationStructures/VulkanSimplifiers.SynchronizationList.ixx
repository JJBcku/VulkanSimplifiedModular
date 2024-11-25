export module VulkanSimplifiers.SynchronizationList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SynchronizationList.Internal;
import VulkanSimplifiers.SynchronizationList.InternalData;
import VulkanSimplifiers.SynchronizationList.Data;

export class SynchronizationListSimplifier
{
public:
	SynchronizationListSimplifier(SynchronizationListInternal& ref);
	~SynchronizationListSimplifier();

	SynchronizationListSimplifier& operator=(const SynchronizationListSimplifier&) noexcept = delete;

	IDObject<AutoCleanupFence> AddFence(bool createSignaled = true, size_t addOnReserve = 0);

	bool WaitOnFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs, bool waitForAll, std::uint64_t timeout = std::numeric_limits<std::uint64_t>::max());
	void ResetFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs);

	IDObject<AutoCleanupSemaphore> AddSemaphore(size_t addOnReserve = 0);

private:
	SynchronizationListInternal& _internal;
};