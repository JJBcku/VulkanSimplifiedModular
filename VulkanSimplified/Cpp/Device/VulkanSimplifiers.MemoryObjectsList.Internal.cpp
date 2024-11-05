module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.MemoryObjectsList.Internal;

MemoryObjectsListInternal::MemoryObjectsListInternal(const MemoryDataList& memoryHeapList, const MemoryListCreationData& creationData)
{
	heapCount = memoryHeapList.heapAmount;

	for (size_t i = 0; i < heapCount; ++i)
	{
		memoryHeapData[i].heapSize = memoryHeapList.memoryHeaps[i].size;
		memoryHeapData[i].properties = memoryHeapList.memoryHeaps[i].properties;
	}

	typeCount = memoryHeapList.memoryTypeAmount;

	for (size_t i = 0; i < typeCount; ++i)
	{
		memoryTypeData[i].emplace(memoryHeapList.memoryTypes[i], creationData.memoryInitialAllocationReservations[i]);
	}
}

MemoryObjectsListInternal::~MemoryObjectsListInternal()
{
}
