export module VulkanSimplifiers.SynchronizationList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SynchronizationList.CreationData;

export class SynchronizationListInternal
{
public:
	SynchronizationListInternal(const SynchronizationListCreationData& createInfo);
	~SynchronizationListInternal();

private:
	std::uint64_t stump;
};