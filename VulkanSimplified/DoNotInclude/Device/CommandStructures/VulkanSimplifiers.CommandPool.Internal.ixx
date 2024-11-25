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

	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);
	std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);

	PrimaryNIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID);
	SecondaryNIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID);

	const PrimaryNIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID) const;
	const SecondaryNIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID) const;

private:
	VkDevice _device;
	VkCommandPool _commandPool;

	VkQueue _queue;

	UnsortedList<std::unique_ptr<PrimaryNIRCommandBufferInternal>> _primaryBufferList;
	UnsortedList<std::unique_ptr<SecondaryNIRCommandBufferInternal>> _secondaryBufferList;
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

	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);
	std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);

	PrimaryIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID);
	SecondaryIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID);

	const PrimaryIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID) const;
	const SecondaryIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID) const;

private:
	VkDevice _device;
	VkCommandPool _commandPool;

	VkQueue _queue;

	UnsortedList<std::unique_ptr<PrimaryIRCommandBufferInternal>> _primaryBufferList;
	UnsortedList<std::unique_ptr<SecondaryIRCommandBufferInternal>> _secondaryBufferList;
};