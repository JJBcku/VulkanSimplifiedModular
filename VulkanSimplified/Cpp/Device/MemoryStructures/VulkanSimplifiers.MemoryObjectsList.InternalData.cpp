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
	rhs._totalSize = 0;
	rhs._usedSize = 0;
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
	rhs._totalSize = 0;
	rhs._usedSize = 0;
	return *this;
}

size_t MemoryAllocationData::GetTotalSize() const
{
	return _totalSize;
}

size_t MemoryAllocationData::GetFreeSize() const
{
	assert(_totalSize >= _usedSize);
	return _totalSize - _usedSize;
}

size_t MemoryAllocationData::BindImage(VkImage image, size_t size, size_t aligment, size_t addOnReserve)
{
	CheckSuballocationVectorSize(addOnReserve);

	auto memoryAddresses = FindMemoryAdressAndVectorIndexForSuballocation(size, aligment);

	if (vkBindImageMemory(_device, image, _memory, memoryAddresses.first) != VK_SUCCESS)
		throw std::runtime_error("MemoryAllocationData::BindImage Error: Program failed to bind image to memory!");

	SuballocationInternalData add;
	add.beggining = memoryAddresses.first;
	add.size = size;

	_usedSize += size;

	_suballocationData.insert(_suballocationData.begin() + static_cast<std::int64_t>(memoryAddresses.second), add);

	return memoryAddresses.first;
}

bool MemoryAllocationData::RemoveSuballocation(size_t beggining, bool throwOnNotFound)
{
	for (auto it = _suballocationData.begin(); it < _suballocationData.end(); ++it)
	{
		if (it->beggining == beggining)
		{
			assert(it->size <= _usedSize);
			_usedSize -= it->size;
			_suballocationData.erase(it);
			return true;
		}
	}

	if (throwOnNotFound)
		throw std::runtime_error("MemoryAllocationData::RemoveSuballocation Error: Program tried to remove non-existent suballocation!");

	return false;
}

void MemoryAllocationData::CheckSuballocationVectorSize(size_t addOnReserve)
{
	if (_suballocationData.size() == _suballocationData.capacity())
	{
		if (addOnReserve == 0)
		{
			if (_suballocationData.capacity() == 0)
				_suballocationData.reserve(1);
			else
				_suballocationData.reserve(_suballocationData.capacity() << 1);
		}
		else
		{
			_suballocationData.reserve(_suballocationData.capacity() + addOnReserve);
		}
	}
}

std::pair<size_t, size_t> MemoryAllocationData::FindMemoryAdressAndVectorIndexForSuballocation(size_t size, size_t aligment)
{
	std::pair<size_t, size_t> ret;

	std::optional<size_t> beggining;
	size_t currentPoint = 0;
	size_t i;

	if (_totalSize >= size)
	{
		if (_suballocationData.empty())
		{
			beggining = 0;
			i = 0;
		}
		else
		{
			for (i = 0; i < _suballocationData.size(); ++i)
			{
				if (currentPoint < _suballocationData[i].beggining)
				{
					size_t gapSize = _suballocationData[i].beggining - currentPoint;
					if (gapSize >= size)
					{
						beggining = currentPoint;
						break;
					}
				}

				currentPoint = _suballocationData[i].beggining + _suballocationData[i].size;
				if (currentPoint % aligment != 0)
				{
					currentPoint = (currentPoint / aligment) + 1;
					currentPoint *= aligment;
				}
			}

			if (!beggining.has_value() && _totalSize > currentPoint)
			{
				size_t endSize = _totalSize - currentPoint;
				if (endSize >= size)
				{
					beggining = currentPoint;
				}
			}
		}
	}
	else
		throw std::runtime_error("MemoryAllocationData::FindMemoryAdressAndVectorIndexForSuballocation Error: Program tried to suballocate memory chunk bigger than the whole memory allocation!");

	if (!beggining.has_value())
		throw std::runtime_error("MemoryAllocationData::FindMemoryAdressAndVectorIndexForSuballocation Error: Program failed to find a proper beggining point for a suballocation!");

	ret.first = beggining.value();
	ret.second = i;

	return ret;
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

size_t MemoryTypeInternalData::BindImage(IDObject<MemoryAllocationData> allocationID, VkImage image, size_t size, size_t aligment, size_t addOnReserve)
{
	return _allocationsList.GetObject(allocationID).BindImage(image, size, aligment, addOnReserve);
}

bool MemoryTypeInternalData::CheckForAllocationsExistence(IDObject<MemoryAllocationData> allocationID)
{
	return _allocationsList.CheckForID(allocationID);
}

bool MemoryTypeInternalData::RemoveSuballocation(IDObject<MemoryAllocationData> allocationID, size_t beggining, bool throwOnNotFound)
{
	return _allocationsList.GetObject(allocationID).RemoveSuballocation(beggining, throwOnNotFound);
}