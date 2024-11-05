module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.MemoryObjectsList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.Common.MemoryData;
import VulkanSimplifiers.MemoryObjectsList.InternalData;
import VulkanSimplifiers.MemoryObjectsList.CreationData;

export class MemoryObjectsListInternal
{
public:
	MemoryObjectsListInternal(const MemoryDataList& memoryHeapList, const MemoryListCreationData& creationData);
	~MemoryObjectsListInternal();

	MemoryObjectsListInternal(const MemoryObjectsListInternal&) noexcept = delete;
	MemoryObjectsListInternal(MemoryObjectsListInternal&&) noexcept = delete;

	MemoryObjectsListInternal& operator=(const MemoryObjectsListInternal&) noexcept = delete;
	MemoryObjectsListInternal& operator=(MemoryObjectsListInternal&&) noexcept = delete;

private:
	size_t heapCount;
	std::array<HeapInternalData, VK_MAX_MEMORY_HEAPS> memoryHeapData;

	size_t typeCount;
	std::array<std::optional<MemoryTypeInternalData>, VK_MAX_MEMORY_TYPES> memoryTypeData;
};