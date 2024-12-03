module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.CommandPoolQFGroupList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.CommandPoolQFGroupList.CreationData;
import VulkanSimplifiers.CommandPool.Internal;

import VulkanSimplifiers.LogicalDeviceCore.Internal;

import VulkanSimplifiers.ImageDataList.Internal;
import VulkanSimplifiers.ImageDataList.InternalData;
import VulkanSimplifiers.ImageDataList.Data;

import VulkanSimplifiers.DeviceRenderPassData.Internal;
import VulkanSimplifiers.DeviceRenderPassData.InternalData;
import VulkanSimplifiers.DeviceRenderPassData.Data;

import VulkanSimplifiers.SharedRenderPassData.Internal;
import VulkanSimplifiers.SharedRenderPassData.InternalData;
import VulkanSimplifiers.SharedRenderPassData.Data;

import VulkanSimplifiers.DevicePipelineData.Internal;
import VulkanSimplifiers.DevicePipelineData.InternalData;
import VulkanSimplifiers.DevicePipelineData.Data;

import VulkanSimplifiers.SynchronizationList.Internal;
import VulkanSimplifiers.SynchronizationList.InternalData;
import VulkanSimplifiers.SynchronizationList.Data;

import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.WindowList.Data;

import VulkanSimplifiers.Window.Internal;
import VulkanSimplifiers.Window.InternalData;
import VulkanSimplifiers.Window.Data;

import VulkanSimplifiers.CommandPoolQFGroupList.Data;
import VulkanSimplifiers.Common.PipelineStageFlags.Internal;

export class CommandPoolQFGroupListInternal
{
public:
	CommandPoolQFGroupListInternal(const LogicalDeviceCoreInternal& deviceCore, const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
		const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
		WindowListInternal& windowList, const CommandPoolQFGroupListCreationData& creationData, size_t queueFamily);
	~CommandPoolQFGroupListInternal();

	CommandPoolQFGroupListInternal(const CommandPoolQFGroupListInternal&) noexcept = delete;
	CommandPoolQFGroupListInternal(CommandPoolQFGroupListInternal&&) noexcept = delete;

	CommandPoolQFGroupListInternal& operator=(const CommandPoolQFGroupListInternal&) noexcept = delete;
	CommandPoolQFGroupListInternal& operator=(CommandPoolQFGroupListInternal&&) noexcept = delete;

	IDObject<std::unique_ptr<NIRCommandPoolInternal>> AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);
	IDObject<std::unique_ptr<IRCommandPoolInternal>> AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve);

	NIRCommandPoolInternal& GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID);
	IRCommandPoolInternal& GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID);

	const NIRCommandPoolInternal& GetCommandPoolWithoutIndividualResetSimplifier(IDObject<std::unique_ptr<NIRCommandPoolInternal>> poolID) const;
	const IRCommandPoolInternal& GetCommandPoolWithIndividualResetSimplifier(IDObject<std::unique_ptr<IRCommandPoolInternal>> poolID) const;

	void SubmitBuffers(size_t queueID, const std::vector<CommandBufferSubmitInfo>& submitInfos, std::optional<IDObject<AutoCleanupFence>> fenceID);

private:
	const LogicalDeviceCoreInternal& _deviceCore;

	const DeviceRenderPassDataInternal& _deviceRenderPassData;
	const SharedRenderPassDataInternal& _sharedRenderPassData;

	const DevicePipelineDataInternal& _devicePipelineData;
	const SynchronizationListInternal& _synchronizationList;

	const ImageDataListInternal& _imageList;

	WindowListInternal& _windowList;

	VkDevice _device;

	size_t _queueFamily;

	UnsortedList<std::unique_ptr<NIRCommandPoolInternal>> _noIndividualResetCommandPoolList;
	UnsortedList<std::unique_ptr<IRCommandPoolInternal>> _individualResetCommandPoolList;

	VkCommandBuffer GetCommandBuffer(CommandBufferGenericID bufferID) const;

	VkCommandBuffer GetCommandBuffer(IDObject<std::unique_ptr<NIRCommandPoolInternal>> commandPoolID,
		IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> commandBufferID) const;
	VkCommandBuffer GetCommandBuffer(IDObject<std::unique_ptr<NIRCommandPoolInternal>> commandPoolID,
		IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> commandBufferID) const;
	VkCommandBuffer GetCommandBuffer(IDObject<std::unique_ptr<IRCommandPoolInternal>> commandPoolID,
		IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> commandBufferID) const;
	VkCommandBuffer GetCommandBuffer(IDObject<std::unique_ptr<IRCommandPoolInternal>> commandPoolID,
		IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> commandBufferID) const;
};