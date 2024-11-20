export module VulkanSimplifiers.CommandPoolList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPoolList.Internal;
import VulkanSimplifiers.CommandPool.Data;

import VulkanSimplifiers.NIRCommandPool;
import VulkanSimplifiers.IRCommandPool;

import VulkanSimplifiers.CommandPool.Internal;

export class CommandPoolListSimplifier
{
public:
	CommandPoolListSimplifier(CommandPoolListInternal& ref);
	~CommandPoolListSimplifier();

	CommandPoolListSimplifier(const CommandPoolListSimplifier&) noexcept = delete;

	CommandPoolListSimplifier& operator= (const CommandPoolListSimplifier&) noexcept = delete;

	IDObject<NIRCommandPoolInternal> AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);
	IDObject<IRCommandPoolInternal> AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);

	NIRCommandPoolSimplifier GetCommandPoolWithoutIndividualResetSimplifier(IDObject<NIRCommandPoolInternal> poolID);
	IRCommandPoolSimplifier GetCommandPoolWithIndividualResetSimplifier(IDObject<IRCommandPoolInternal> poolID);

	const NIRCommandPoolSimplifier GetCommandPoolWithoutIndividualResetSimplifier(IDObject<NIRCommandPoolInternal> poolID) const;
	const IRCommandPoolSimplifier GetCommandPoolWithIndividualResetSimplifier(IDObject<IRCommandPoolInternal> poolID) const;

private:
	CommandPoolListInternal& _internal;
};