module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SynchronizationList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SynchronizationList.CreationData;
import VulkanSimplifiers.SynchronizationList.InternalData;

export class SynchronizationListInternal
{
public:
	SynchronizationListInternal(VkDevice device, const SynchronizationListCreationData& createInfo);
	~SynchronizationListInternal();

	IDObject<AutoCleanupFence> AddFence(bool createSignaled, size_t addOnReserve);
	VkFence GetFence(IDObject<AutoCleanupFence> fenceIDs) const;

	bool WaitOnFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs, bool waitForAll, std::uint64_t timeout);
	void ResetFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs);

	IDObject<AutoCleanupSemaphore> AddSemaphore(size_t addOnReserve);
	VkSemaphore GetSemaphore(IDObject<AutoCleanupSemaphore> semaphoreID) const;

private:
	VkDevice _device;

	UnsortedList<AutoCleanupFence> _fenceList;
	UnsortedList<AutoCleanupSemaphore> _semaphoreList;
};