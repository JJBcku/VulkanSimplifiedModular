export module VulkanSimplifiers.SynchronizationList;

import VulkanSimplifiers.SynchronizationList.Internal;

export class SynchronizationListSimplifier
{
public:
	SynchronizationListSimplifier(SynchronizationListInternal& ref);
	~SynchronizationListSimplifier();

	SynchronizationListSimplifier& operator=(const SynchronizationListSimplifier&) noexcept = delete;

private:
	SynchronizationListInternal& _internal;
};