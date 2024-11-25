module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.CommandPoolList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.CommandPoolList.CreationData;
import VulkanSimplifiers.CommandPool.Internal;

import VulkanSimplifiers.LogicalDeviceCore.Internal;

export class CommandPoolListInternal
{
public:
	CommandPoolListInternal(const LogicalDeviceCoreInternal& deviceCore, const CommandPoolListCreationData& creationData);
	~CommandPoolListInternal();

	CommandPoolListInternal(const CommandPoolListInternal&) noexcept = delete;
	CommandPoolListInternal(CommandPoolListInternal&&) noexcept = delete;

	CommandPoolListInternal& operator=(const CommandPoolListInternal&) noexcept = delete;
	CommandPoolListInternal& operator=(CommandPoolListInternal&&) noexcept = delete;

	IDObject<std::unique_ptr<NIRCommandPoolInternal>> AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);
	IDObject<std::unique_ptr<IRCommandPoolInternal>> AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);

	NIRCommandPoolInternal& GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID);
	IRCommandPoolInternal& GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID);

	const NIRCommandPoolInternal& GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID) const;
	const IRCommandPoolInternal& GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID) const;

private:
	const LogicalDeviceCoreInternal& _deviceCore;

	VkDevice _device;

	UnsortedList<std::unique_ptr<NIRCommandPoolInternal>> _noIndividualResetCommandPoolList;
	UnsortedList<std::unique_ptr<IRCommandPoolInternal>> _individualResetCommandPoolList;
};