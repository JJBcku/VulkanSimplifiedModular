module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.CommandPool.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.CommandBuffer.Internal;

export class NIRCommandPoolInternal
{
public:
	NIRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, VkQueue queue, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
	~NIRCommandPoolInternal();

	NIRCommandPoolInternal(const NIRCommandPoolInternal&) noexcept = delete;
	NIRCommandPoolInternal(NIRCommandPoolInternal&& rhs) noexcept;

	NIRCommandPoolInternal& operator=(const NIRCommandPoolInternal&) noexcept = delete;
	NIRCommandPoolInternal& operator=(NIRCommandPoolInternal&& rhs) noexcept;

	std::vector<IDObject<PrimaryNIRCommandBufferInternal>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);
	std::vector<IDObject<SecondaryNIRCommandBufferInternal>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);

private:
	VkDevice _device;
	VkCommandPool _commandPool;

	VkQueue _queue;

	UnsortedList<PrimaryNIRCommandBufferInternal> _primaryBufferList;
	UnsortedList<SecondaryNIRCommandBufferInternal> _secondaryBufferList;
};

export class IRCommandPoolInternal
{
public:
	IRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, VkQueue queue, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
	~IRCommandPoolInternal();

	IRCommandPoolInternal(const IRCommandPoolInternal&) noexcept = delete;
	IRCommandPoolInternal(IRCommandPoolInternal&& rhs) noexcept;

	IRCommandPoolInternal& operator=(const IRCommandPoolInternal&) noexcept = delete;
	IRCommandPoolInternal& operator=(IRCommandPoolInternal&& rhs) noexcept;

	std::vector<IDObject<PrimaryIRCommandBufferInternal>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);
	std::vector<IDObject<SecondaryIRCommandBufferInternal>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);

private:
	VkDevice _device;
	VkCommandPool _commandPool;

	VkQueue _queue;

	UnsortedList<PrimaryIRCommandBufferInternal> _primaryBufferList;
	UnsortedList<SecondaryIRCommandBufferInternal> _secondaryBufferList;
};