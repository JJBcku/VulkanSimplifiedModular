module VulkanSimplifiers.Common.MemoryData;

MemoryTypeData::MemoryTypeData()
{
	heapIndex = std::numeric_limits<size_t>::max();
	properties = std::numeric_limits<MemoryTypeProperties>::max();
}

MemoryHeapData::MemoryHeapData()
{
	size = 0;
	properties = std::numeric_limits<MemoryHeapProperties>::max();
}

MemoryDataList::MemoryDataList()
{
	heapAmount = 0;
	memoryTypeAmount = 0;
}