export module VulkanSimplifiers.CommandPoolQFGroupList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPoolQFGroupList.Internal;
import VulkanSimplifiers.CommandPool.Data;

import VulkanSimplifiers.NIRCommandPool;
import VulkanSimplifiers.IRCommandPool;

import VulkanSimplifiers.CommandPool.Internal;
import VulkanSimplifiers.CommandPoolQFGroupList.Data;

export class CommandPoolQFGroupListSimplifier
{
public:
	CommandPoolQFGroupListSimplifier(CommandPoolQFGroupListInternal& ref);
	~CommandPoolQFGroupListSimplifier();

	CommandPoolQFGroupListSimplifier& operator=(const CommandPoolQFGroupListSimplifier&) noexcept = delete;

	IDObject<std::unique_ptr<NIRCommandPoolInternal>> AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);
	IDObject<std::unique_ptr<IRCommandPoolInternal>> AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);

	NIRCommandPoolSimplifier GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID);
	IRCommandPoolSimplifier GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID);

	const NIRCommandPoolSimplifier GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID) const;
	const IRCommandPoolSimplifier GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID) const;

	void SubmitBuffers(size_t queueID, const std::vector<CommandBufferSubmitInfo>& submitInfos, std::optional<IDObject<AutoCleanupFence>> fenceID);

private:
	CommandPoolQFGroupListInternal& _internal;
};