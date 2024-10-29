module VulkanSimplifiers.Common.MemoryData;

MemoryTypeData::MemoryTypeData()
{
	index = std::numeric_limits<size_t>::max();
	properties = std::numeric_limits<MemoryTypeProperties>::max();
}

MemoryHeapData::MemoryHeapData()
{
	size = 0;
	properties = std::numeric_limits<MemoryHeapProperties>::max();
	memoryTypeAmount = 0;
}

MemoryHeapList::MemoryHeapList()
{
	heapAmount = 0;
}