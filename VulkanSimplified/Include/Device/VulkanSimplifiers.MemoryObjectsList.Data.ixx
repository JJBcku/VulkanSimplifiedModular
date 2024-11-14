export module VulkanSimplifiers.MemoryObjectsList.Data;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.Common.MemoryData;

export class MemoryAllocationData;

export typedef std::pair<IDObject<MemoryAllocationData>, size_t> AllocationFullID;