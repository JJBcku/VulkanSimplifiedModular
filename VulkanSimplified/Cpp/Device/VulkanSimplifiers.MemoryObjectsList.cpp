module VulkanSimplifiers.MemoryObjectsList;

MemoryObjectsListSimplifier::MemoryObjectsListSimplifier(MemoryObjectsListInternal& ref) : _internal(ref)
{
}

MemoryObjectsListSimplifier::~MemoryObjectsListSimplifier()
{
}

AllocationFullID MemoryObjectsListSimplifier::AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
	const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve)
{
	return _internal.AllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserve);
}

std::optional<AllocationFullID> MemoryObjectsListSimplifier::TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
	const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve)
{
	return _internal.TryToAllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserve);
}

bool MemoryObjectsListSimplifier::FreeMemory(std::pair<IDObject<MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound)
{
	return _internal.FreeMemory(memoryID, throwOnNotFound);
}
