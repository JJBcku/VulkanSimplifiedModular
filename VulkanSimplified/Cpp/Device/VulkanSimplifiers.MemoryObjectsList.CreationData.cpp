module VulkanSimplifiers.MemoryObjectsList.CreationData;

MemoryListCreationData::MemoryListCreationData()
{
	std::memset(&memoryInitialAllocationReservations, 0, sizeof(memoryInitialAllocationReservations));
}