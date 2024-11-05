module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.MemoryObjectsList.InternalData;

HeapInternalData::HeapInternalData()
{
	heapSize = 0;
	usedSize = 0;
	properties = std::numeric_limits<MemoryHeapProperties>::max();
}

SuballocationInternalData::SuballocationInternalData()
{
	beggining = std::numeric_limits<size_t>::max();
	size = 0;
}

AllocationInternalData::AllocationInternalData(VkDevice device, VkDeviceMemory memory, size_t totalSize, size_t reservedSuballocations, bool mapMemory) : _device(device),
_memory(memory), _totalSize(totalSize), _usedSize(0)
{
	_data = nullptr;
	_suballocationData.reserve(reservedSuballocations);

	if (mapMemory)
	{
		if (vkMapMemory(_device, _memory, 0, VK_WHOLE_SIZE, 0, reinterpret_cast<void**>(&_data)) != VK_SUCCESS)
			throw std::runtime_error("AllocationInternalData::AllocationInternalData Error: Program failed to map the allocation memory!");
	}
}

AllocationInternalData::~AllocationInternalData()
{
	if (_memory != VK_NULL_HANDLE)
	{
		vkFreeMemory(_device, _memory, nullptr);
	}
}

VkDeviceMemory AllocationInternalData::GetDeviceMemory() const
{
	return _memory;
}

MemoryTypeInternalData::MemoryTypeInternalData(const MemoryTypeData& typeData, size_t reservedAllocation) : _heapIndex(typeData.heapIndex), _properties(typeData.properties),
_allocationsList(reservedAllocation)
{
}

MemoryTypeInternalData::~MemoryTypeInternalData()
{
}