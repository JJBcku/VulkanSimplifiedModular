module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.MemoryObjectsList.InternalData;

HeapInternalData::HeapInternalData()
{
	heapSize = 0;
	usedSize = 0;
	properties = std::numeric_limits<MemoryHeapProperties>::max();
}

size_t HeapInternalData::GetFreeSize() const
{
	assert(heapSize >= usedSize);

	return heapSize - usedSize;
}

SuballocationInternalData::SuballocationInternalData()
{
	beggining = std::numeric_limits<size_t>::max();
	size = 0;
}

MemoryAllocationData::MemoryAllocationData(VkDevice device, VkDeviceMemory memory, size_t totalSize, size_t reservedSuballocations, bool mapMemory) : _device(device),
_memory(memory), _totalSize(totalSize), _usedSize(0)
{
	_data = nullptr;
	_suballocationData.reserve(reservedSuballocations);

	if (mapMemory)
	{
		if (vkMapMemory(_device, _memory, 0, VK_WHOLE_SIZE, 0, reinterpret_cast<void**>(&_data)) != VK_SUCCESS)
			throw std::runtime_error("MemoryAllocationData::MemoryAllocationData Error: Program failed to map the allocation memory!");
	}
}

MemoryAllocationData::~MemoryAllocationData()
{
	if (_memory != VK_NULL_HANDLE)
	{
		vkFreeMemory(_device, _memory, nullptr);
	}
}

MemoryAllocationData::MemoryAllocationData(MemoryAllocationData&& rhs) noexcept : _device(rhs._device), _memory(rhs._memory), _data(rhs._data), _totalSize(rhs._totalSize),
	_usedSize(rhs._usedSize), _suballocationData(std::move(rhs._suballocationData))
{
	rhs._device = VK_NULL_HANDLE;
	rhs._memory = VK_NULL_HANDLE;

	rhs._data = nullptr;
	_totalSize = 0;
	_usedSize = 0;
}

MemoryAllocationData& MemoryAllocationData::operator=(MemoryAllocationData&& rhs) noexcept
{
	_device = rhs._device;
	_memory = rhs._memory;
	_data = rhs._data;
	_totalSize = rhs._totalSize;
	_usedSize = rhs._usedSize;

	rhs._device = VK_NULL_HANDLE;
	rhs._memory = VK_NULL_HANDLE;

	rhs._data = nullptr;
	_totalSize = 0;
	_usedSize = 0;
	return *this;
}

size_t MemoryAllocationData::GetTotalSize() const
{
	return _totalSize;
}

MemoryTypeInternalData::MemoryTypeInternalData(VkDevice device, const MemoryTypeData& typeData, std::uint32_t typeIndex, size_t reservedAllocation) : _device(device),
	_heapIndex(static_cast<std::uint32_t>(typeData.heapIndex)), _typeIndex(typeIndex), _properties(typeData.properties), _allocationsList(reservedAllocation)
{
}

MemoryTypeInternalData::~MemoryTypeInternalData()
{
}

MemoryTypeInternalData::MemoryTypeInternalData(MemoryTypeInternalData&& rhs) noexcept : _device(rhs._device), _heapIndex(rhs._heapIndex), _typeIndex(rhs._typeIndex),
	_properties(rhs._properties), _allocationsList(std::move(rhs._allocationsList))
{
	rhs._device = VK_NULL_HANDLE;
	rhs._heapIndex = std::numeric_limits<std::uint32_t>::max();
	rhs._typeIndex = std::numeric_limits<std::uint32_t>::max();
	rhs._properties = std::numeric_limits<MemoryTypeProperties>::max();
}

MemoryTypeInternalData& MemoryTypeInternalData::operator=(MemoryTypeInternalData&& rhs) noexcept
{
	_device = rhs._device;
	_heapIndex = rhs._heapIndex;
	_typeIndex = rhs._typeIndex;
	_properties = rhs._properties;
	_allocationsList = std::move(rhs._allocationsList);

	rhs._device = VK_NULL_HANDLE;
	rhs._heapIndex = std::numeric_limits<std::uint32_t>::max();
	rhs._typeIndex = std::numeric_limits<std::uint32_t>::max();
	rhs._properties = std::numeric_limits<MemoryTypeProperties>::max();
	return *this;
}

IDObject<MemoryAllocationData> MemoryTypeInternalData::AddMemoryAllocation(size_t dataSize, size_t initialSuballocationsReserved, size_t addOnReserve)
{
	assert(dataSize > 0);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = dataSize;
	allocInfo.memoryTypeIndex = _typeIndex;

	VkDeviceMemory allocation = VK_NULL_HANDLE;

	if (vkAllocateMemory(_device, &allocInfo, nullptr, &allocation) != VK_SUCCESS)
		throw std::runtime_error("MemoryTypeInternalData::AddMemoryAllocation Error: Program failed to allocate memory!");

	bool mapMemory = (_properties & HOST_COHERENT) == HOST_COHERENT;

	return _allocationsList.AddObject(MemoryAllocationData(_device, allocation, dataSize, initialSuballocationsReserved, mapMemory), addOnReserve);
}

bool MemoryTypeInternalData::FreeMemory(IDObject<MemoryAllocationData> memoryId, bool throwOnNotFound)
{
	return _allocationsList.RemoveObject(memoryId, throwOnNotFound);
}

std::uint32_t MemoryTypeInternalData::GetHeapIndex() const
{
	return _heapIndex;
}

std::uint32_t MemoryTypeInternalData::GetTypeIndex() const
{
	return _typeIndex;
}

MemoryTypeProperties MemoryTypeInternalData::GetProperties() const
{
	return _properties;
}

size_t MemoryTypeInternalData::GetMemoryAllocationsSize(IDObject<MemoryAllocationData> allocationID) const
{
	return _allocationsList.GetConstObject(allocationID).GetTotalSize();
}