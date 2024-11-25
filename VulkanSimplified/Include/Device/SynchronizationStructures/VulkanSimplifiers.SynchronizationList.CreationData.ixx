export module VulkanSimplifiers.SynchronizationList.CreationData;

import std;

export struct SynchronizationListCreationData
{
	std::uint64_t fenceListInitialCapacity;

	SynchronizationListCreationData();
};