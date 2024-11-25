export module VulkanSimplifiers.SynchronizationList.CreationData;

import std;

export struct SynchronizationListCreationData
{
	std::uint64_t fenceListInitialCapacity;
	std::uint64_t semaphoreListInitialCapacity;

	SynchronizationListCreationData();
};