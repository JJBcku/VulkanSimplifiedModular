module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.MemoryObjectsList.CreationData;

import std;

export typedef std::array<size_t, VK_MAX_MEMORY_TYPES> InitAllocArray;

export struct MemoryListCreationData
{
	InitAllocArray memoryInitialAllocationReservations;

	MemoryListCreationData();
};