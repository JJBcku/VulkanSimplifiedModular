module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.CommandPool.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.CommandBuffer.Internal;

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

import VulkanSimplifiers.LogicalDeviceCore.Internal;
import VulkanSimplifiers.LogicalDeviceCore.InternalData;
import VulkanSimplifiers.LogicalDeviceCore.Data;

export class NIRCommandPoolInternal
{
public:
	NIRCommandPoolInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
		const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
		WindowListInternal& windowList, VkDevice device, VkCommandPool commandPool, VkQueue queue, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
	~NIRCommandPoolInternal();

	NIRCommandPoolInternal(const NIRCommandPoolInternal&) noexcept = delete;
	NIRCommandPoolInternal(NIRCommandPoolInternal&& rhs) noexcept = delete;

	NIRCommandPoolInternal& operator=(const NIRCommandPoolInternal&) noexcept = delete;
	NIRCommandPoolInternal& operator=(NIRCommandPoolInternal&& rhs) noexcept = delete;

	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);
	std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);

	PrimaryNIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID);
	SecondaryNIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID);

	const PrimaryNIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID) const;
	const SecondaryNIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID) const;

	void ResetCommandPool(bool freeResources);

private:
	const LogicalDeviceCoreInternal& _core;

	const DeviceRenderPassDataInternal& _deviceRenderPassData;
	const SharedRenderPassDataInternal& _sharedRenderPassData;

	const DevicePipelineDataInternal& _devicePipelineData;
	const SynchronizationListInternal& _synchronizationList;

	const ImageDataListInternal& _imageList;

	WindowListInternal& _windowList;

	VkDevice _device;
	VkCommandPool _commandPool;

	VkQueue _queue;

	UnsortedList<std::unique_ptr<PrimaryNIRCommandBufferInternal>> _primaryBufferList;
	UnsortedList<std::unique_ptr<SecondaryNIRCommandBufferInternal>> _secondaryBufferList;
};

export class IRCommandPoolInternal
{
public:
	IRCommandPoolInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
		const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
		WindowListInternal& windowList, VkDevice device, VkCommandPool commandPool, VkQueue queue, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
	~IRCommandPoolInternal();

	IRCommandPoolInternal(const IRCommandPoolInternal&) noexcept = delete;
	IRCommandPoolInternal(IRCommandPoolInternal&& rhs) noexcept = delete;

	IRCommandPoolInternal& operator=(const IRCommandPoolInternal&) noexcept = delete;
	IRCommandPoolInternal& operator=(IRCommandPoolInternal&& rhs) noexcept = delete;

	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);
	std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve);

	PrimaryIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID);
	SecondaryIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID);

	const PrimaryIRCommandBufferInternal& GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID) const;
	const SecondaryIRCommandBufferInternal& GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID) const;

	void ResetCommandPool(bool freeResources);

private:
	const LogicalDeviceCoreInternal& _core;

	const DeviceRenderPassDataInternal& _deviceRenderPassData;
	const SharedRenderPassDataInternal& _sharedRenderPassData;

	const DevicePipelineDataInternal& _devicePipelineData;
	const SynchronizationListInternal& _synchronizationList;

	const ImageDataListInternal& _imageList;

	WindowListInternal& _windowList;

	VkDevice _device;
	VkCommandPool _commandPool;

	VkQueue _queue;

	UnsortedList<std::unique_ptr<PrimaryIRCommandBufferInternal>> _primaryBufferList;
	UnsortedList<std::unique_ptr<SecondaryIRCommandBufferInternal>> _secondaryBufferList;
};