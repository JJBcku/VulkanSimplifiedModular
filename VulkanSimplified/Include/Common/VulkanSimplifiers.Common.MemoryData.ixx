module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Common.MemoryData;

import std;

export typedef std::uint64_t MemoryTypeProperties;

export enum MemoryTypePropertyFlags : MemoryTypeProperties
{
	DEVICE_LOCAL = 0x1,
	HOST_VISIBLE = 0x2,
	HOST_COHERENT = 0x4,
	HOST_UNCACHED = 0x8,
	LAZYLY_ALLOCATED = 0x10,
	PROTECTED = 0x20,
};

export struct MemoryTypeData
{
	size_t heapIndex;
	MemoryTypeProperties properties;

	MemoryTypeData();
};

export typedef std::uint64_t MemoryHeapProperties;

export enum MemoryHeapPropertyFlags : MemoryHeapProperties
{
	DEVICE_LOCAL_HEAP = 0x1,
	MULTI_INSTANCE_HEAP = 0X2,
};

export typedef std::uint64_t MemorySize;

export struct MemoryHeapData
{
	MemorySize size;
	MemoryHeapProperties properties;

	MemoryHeapData();
};

export struct MemoryDataList
{
	size_t heapAmount;
	std::array<MemoryHeapData, VK_MAX_MEMORY_HEAPS> memoryHeaps;

	size_t memoryTypeAmount;
	std::array<MemoryTypeData, VK_MAX_MEMORY_TYPES> memoryTypes;

	MemoryDataList();
};