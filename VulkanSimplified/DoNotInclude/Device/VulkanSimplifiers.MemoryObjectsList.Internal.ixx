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
	MemoryObjectsListInternal(VkDevice device, const MemoryDataList& memoryHeapList, const MemoryListCreationData& creationData);
	~MemoryObjectsListInternal();

	MemoryObjectsListInternal(const MemoryObjectsListInternal&) noexcept = delete;
	MemoryObjectsListInternal(MemoryObjectsListInternal&&) noexcept = delete;

	MemoryObjectsListInternal& operator=(const MemoryObjectsListInternal&) noexcept = delete;
	MemoryObjectsListInternal& operator=(MemoryObjectsListInternal&&) noexcept = delete;

	std::pair<IDObject<MemoryAllocationData>, size_t> AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve);

	std::optional<std::pair<IDObject<MemoryAllocationData>, size_t>> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve);

	bool FreeMemory(std::pair<IDObject<MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound);

private:
	size_t heapCount;
	std::array<HeapInternalData, VK_MAX_MEMORY_HEAPS> memoryHeapData;

	size_t typeCount;
	std::array<std::optional<MemoryTypeInternalData>, VK_MAX_MEMORY_TYPES> memoryTypeData;
};