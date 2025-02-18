module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.MemoryObjectsList.Internal;

MemoryObjectsListInternal::MemoryObjectsListInternal(VkDevice device, const MemoryDataList& memoryHeapList, const MemoryListCreationData& creationData)
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
		memoryTypeData[i].emplace(device, memoryHeapList.memoryTypes[i], static_cast<std::uint32_t>(i), creationData.memoryInitialAllocationReservations[i]);
	}
}

MemoryObjectsListInternal::~MemoryObjectsListInternal()
{
}

AllocationFullID MemoryObjectsListInternal::AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
	const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve)
{
	std::optional<std::pair<IDObject<MemoryAllocationData>, size_t>> ret;
	assert(memorySize > 0);
	assert(memoryTypeMask > 0);
	assert(!acceptableMemoryTypesProperties.empty());

	for (size_t i = 0; i < acceptableMemoryTypesProperties.size(); ++i)
	{
		for (size_t j = 0; j < typeCount; ++j)
		{
			if (acceptableMemoryTypesProperties[i] != memoryTypeData[j].value().GetProperties())
				continue;

			std::uint32_t memoryBit = 1U << j;

			if ((memoryTypeMask & memoryBit) != memoryBit)
				continue;

			size_t heapIndex = memoryTypeData[j].value().GetHeapIndex();

			if (memoryHeapData[heapIndex].GetFreeSize() < memorySize)
				continue;

			ret.emplace(memoryTypeData[j].value().AddMemoryAllocation(memorySize, initialSuballocationsReserved, addOnReserve), j);

			memoryHeapData[heapIndex].usedSize += memorySize;

			if (ret.has_value())
				return ret.value();
		}
	}

	throw std::runtime_error("MemoryObjectsListInternal::AddMemoryAllocation Error: Program failed to allocate memory!");
}

std::optional<AllocationFullID> MemoryObjectsListInternal::TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
	const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve)
{
	std::optional<AllocationFullID> ret;

	assert(memorySize > 0);
	assert(memoryTypeMask > 0);
	assert(!acceptableMemoryTypesProperties.empty());

	for (size_t i = 0; i < acceptableMemoryTypesProperties.size(); ++i)
	{
		for (size_t j = 0; j < typeCount; ++j)
		{
			if (acceptableMemoryTypesProperties[i] != memoryTypeData[j].value().GetProperties())
				continue;

			std::uint32_t memoryBit = 1U << j;

			if ((memoryTypeMask & memoryBit) != memoryBit)
				continue;

			size_t heapIndex = memoryTypeData[j].value().GetHeapIndex();

			if (memoryHeapData[heapIndex].GetFreeSize() < memorySize)
				continue;

			ret.emplace(memoryTypeData[j].value().AddMemoryAllocation(memorySize, initialSuballocationsReserved, addOnReserve), j);
			memoryHeapData[heapIndex].usedSize += memorySize;

			if (ret.has_value())
				break;
		}

		if (ret.has_value())
			break;
	}

	return ret;
}

size_t MemoryObjectsListInternal::BindImage(AllocationFullID allocationID, VkImage image, size_t size, size_t aligment, size_t addOnReserve)
{
	if (allocationID.second >= typeCount)
		throw std::runtime_error("MemoryObjectsListInternal::BindImage Error: Program tried to access a non-existent memory type!");

	return memoryTypeData[allocationID.second].value().BindImage(allocationID.first, image, size, aligment, addOnReserve);
}

bool MemoryObjectsListInternal::RemoveSuballocation(AllocationFullID allocationID, size_t beggining, bool throwOnNotFound)
{
	if (allocationID.second >= typeCount)
		throw std::runtime_error("MemoryObjectsListInternal::RemoveSuballocation Error: Program tried to access a non-existent memory type!");

	return memoryTypeData[allocationID.second].value().RemoveSuballocation(allocationID.first, beggining, throwOnNotFound);
}

bool MemoryObjectsListInternal::FreeMemory(std::pair<IDObject<MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound)
{
	if (memoryID.second >= typeCount)
		throw std::runtime_error("MemoryObjectsListInternal::FreeMemory Error: Program tried to access a non-existent memory type!");

	auto& memType = memoryTypeData[memoryID.second];
	assert(memType.has_value());

	bool ret = memType.value().CheckForAllocationsExistence(memoryID.first);

	if (!ret && throwOnNotFound)
		throw std::runtime_error("MemoryObjectsListInternal::FreeMemory Error: Program tried to free non-existent memory allocation!");

	if (ret)
	{
		auto& memHeap = memoryHeapData[memType.value().GetHeapIndex()];
		size_t memorySize = memType.value().GetMemoryAllocationsSize(memoryID.first);
		assert(memHeap.usedSize >= memorySize);
		memHeap.usedSize -= memorySize;
		memType.value().FreeMemory(memoryID.first, true);
	}

	return ret;
}
