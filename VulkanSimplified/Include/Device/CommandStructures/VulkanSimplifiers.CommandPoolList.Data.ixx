export module VulkanSimplifiers.CommandPoolList.Data;

import std;
export import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPool.Data;

import VulkanSimplifiers.NIRCommandPool;
export import VulkanSimplifiers.NIRCommandPool.Data;
import VulkanSimplifiers.IRCommandPool;
export import VulkanSimplifiers.IRCommandPool.Data;

export import VulkanSimplifiers.SynchronizationList.Data;
export import VulkanSimplifiers.Common.PipelineStageFlags;

export enum class CommandBufferIDType : std::uint64_t
{
	NIR_PRIMARY = 0x1,
	NIR_SECONDARY = 0x2,
	IR_PRIMARY = 0x4,
	IR_SECONDARY = 0x8,
};

export union CommandBufferGenericID
{
	CommandBufferIDType type;

	struct
	{
		CommandBufferIDType type;
		IDObject<std::unique_ptr<NIRCommandPoolInternal>> commandPoolID;
		IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> commandBufferID;
	} NIRPrimaryID;

	struct
	{
		CommandBufferIDType type;
		IDObject<std::unique_ptr<NIRCommandPoolInternal>> commandPoolID;
		IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> commandBufferID;
	} NIRSecondaryID;

	struct
	{
		CommandBufferIDType type;
		IDObject<std::unique_ptr<IRCommandPoolInternal>> commandPoolID;
		IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> commandBufferID;
	} IRPrimaryID;

	struct
	{
		CommandBufferIDType type;
		IDObject<std::unique_ptr<IRCommandPoolInternal>> commandPoolID;
		IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> commandBufferID;
	} IRSecondaryID;

	CommandBufferGenericID();
};

export struct CommandBufferSubmitInfo
{
	std::vector<std::pair<IDObject<AutoCleanupSemaphore>, PipelineStageFlags>> waitSemaphores;
	std::vector<CommandBufferGenericID> commandBufferIDs;
	std::vector<IDObject<AutoCleanupSemaphore>> signalSemaphores;

	CommandBufferSubmitInfo() = default;
};