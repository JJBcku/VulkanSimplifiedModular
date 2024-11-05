export module VulkanSimplifiers.MemoryObjectsList;

import std;

import VulkanSimplifiers.MemoryObjectsList.Internal;

export class MemoryObjectsListSimplifier
{
public:
	MemoryObjectsListSimplifier(MemoryObjectsListInternal& ref);
	~MemoryObjectsListSimplifier();

	MemoryObjectsListSimplifier& operator=(const MemoryObjectsListSimplifier&) noexcept = delete;

private:
	MemoryObjectsListInternal& _internal;
};