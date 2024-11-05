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
};

export struct SuballocationInternalData
{
	size_t beggining;
	size_t size;

	SuballocationInternalData();
};

export class AllocationInternalData
{
public:
	AllocationInternalData(VkDevice device, VkDeviceMemory memory, size_t totalSize, size_t reservedSuballocations, bool mapMemory);
	~AllocationInternalData();

	VkDeviceMemory GetDeviceMemory() const;

private:
	VkDevice _device;
	VkDeviceMemory _memory;

	unsigned char* _data;

	size_t _totalSize;
	size_t _usedSize;
	std::vector<SuballocationInternalData> _suballocationData;
};

export class MemoryTypeInternalData
{
public:
	MemoryTypeInternalData(const MemoryTypeData& typeData, size_t reservedAllocation);
	~MemoryTypeInternalData();

private:
	size_t _heapIndex;
	MemoryTypeProperties _properties;

	UnsortedList<AllocationInternalData> _allocationsList;
};