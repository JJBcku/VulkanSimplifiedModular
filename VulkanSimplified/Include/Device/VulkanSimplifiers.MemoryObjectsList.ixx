export module VulkanSimplifiers.MemoryObjectsList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.MemoryObjectsList.Data;
import VulkanSimplifiers.MemoryObjectsList.Internal;

export class MemoryObjectsListSimplifier
{
public:
	MemoryObjectsListSimplifier(MemoryObjectsListInternal& ref);
	~MemoryObjectsListSimplifier();

	MemoryObjectsListSimplifier& operator=(const MemoryObjectsListSimplifier&) noexcept = delete;

	AllocationFullID AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved, const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties,
		std::uint32_t memoryTypeMask = std::numeric_limits<std::uint32_t>::max(), size_t addOnReserve = 0);

	std::optional<AllocationFullID> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask = std::numeric_limits<std::uint32_t>::max(), size_t addOnReserve = 0);

	bool FreeMemory(std::pair<IDObject<MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound = true);

private:
	MemoryObjectsListInternal& _internal;
};