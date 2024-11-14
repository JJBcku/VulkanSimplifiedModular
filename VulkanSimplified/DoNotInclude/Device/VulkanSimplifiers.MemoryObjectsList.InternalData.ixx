module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.MemoryObjectsList.InternalData;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.Common.MemoryData;

export struct HeapInternalData
{
	size_t heapSize;
	size_t usedSize;
	MemoryHeapProperties properties;

	HeapInternalData();

	size_t GetFreeSize() const;
};

export struct SuballocationInternalData
{
	size_t beggining;
	size_t size;

	SuballocationInternalData();
};

export class MemoryAllocationData
{
public:
	MemoryAllocationData(VkDevice device, VkDeviceMemory memory, size_t totalSize, size_t reservedSuballocations, bool mapMemory);
	~MemoryAllocationData();

	MemoryAllocationData(const MemoryAllocationData&) noexcept = delete;
	MemoryAllocationData(MemoryAllocationData&& rhs) noexcept;

	MemoryAllocationData& operator=(const MemoryAllocationData&) noexcept = delete;
	MemoryAllocationData& operator=(MemoryAllocationData&& rhs) noexcept;

	size_t GetTotalSize() const;
	size_t GetFreeSize() const;

	size_t BindImage(VkImage image, size_t size, size_t aligment, size_t addOnReserve);

private:
	VkDevice _device;
	VkDeviceMemory _memory;

	unsigned char* _data;

	size_t _totalSize;
	size_t _usedSize;
	std::vector<SuballocationInternalData> _suballocationData;

	void CheckSuballocationVectorSize(size_t addOnReserve);
	std::pair<size_t, size_t> FindMemoryAdressAndVectorIndexForSuballocation(size_t size, size_t aligment);
};

export class MemoryTypeInternalData
{
public:
	MemoryTypeInternalData(VkDevice device, const MemoryTypeData& typeData, std::uint32_t typeIndex, size_t reservedAllocation);
	~MemoryTypeInternalData();

	MemoryTypeInternalData(const MemoryTypeInternalData&) noexcept = delete;
	MemoryTypeInternalData(MemoryTypeInternalData&& rhs) noexcept;

	MemoryTypeInternalData& operator=(const MemoryTypeInternalData&) noexcept = delete;
	MemoryTypeInternalData& operator=(MemoryTypeInternalData&& rhs) noexcept;

	IDObject<MemoryAllocationData> AddMemoryAllocation(size_t dataSize, size_t initialSuballocationsReserved, size_t addOnReserve);

	bool FreeMemory(IDObject<MemoryAllocationData> memoryId, bool throwOnNotFound);

	std::uint32_t GetHeapIndex() const;
	std::uint32_t GetTypeIndex() const;
	MemoryTypeProperties GetProperties() const;

	size_t GetMemoryAllocationsSize(IDObject<MemoryAllocationData> allocationID) const;

	size_t BindImage(IDObject<MemoryAllocationData> allocationID, VkImage image, size_t size, size_t aligment, size_t addOnReserve);

private:
	VkDevice _device;

	std::uint32_t _heapIndex;
	std::uint32_t _typeIndex;
	MemoryTypeProperties _properties;

	UnsortedList<MemoryAllocationData> _allocationsList;
};