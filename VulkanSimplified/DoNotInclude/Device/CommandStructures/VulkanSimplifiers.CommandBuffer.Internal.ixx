module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.CommandBuffer.Internal;

import VulkanSimplifiers.CommonCommandBuffer.Data;

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

export class AutoCleanUpCommandBuffer
{
public:
	AutoCleanUpCommandBuffer(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData, const SharedRenderPassDataInternal& sharedRenderPassData,
		const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList, const ImageDataListInternal& imageList,
		WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~AutoCleanUpCommandBuffer();

	AutoCleanUpCommandBuffer(const AutoCleanUpCommandBuffer&) noexcept = delete;
	AutoCleanUpCommandBuffer(AutoCleanUpCommandBuffer&& rhs) noexcept = delete;

	AutoCleanUpCommandBuffer& operator=(const AutoCleanUpCommandBuffer&) noexcept = delete;
	AutoCleanUpCommandBuffer& operator=(AutoCleanUpCommandBuffer&& rhs) noexcept = delete;

	VkCommandBuffer GetCommandBuffer() const;

	void BeginRecording(CommandBufferUsage usage);
	void EndRecording();

	void BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID);

	void Draw(std::uint32_t vertexCount, std::uint32_t instanceCount, std::uint32_t firstVertex, std::uint32_t firstInstance);

	bool AcquireNextImage(std::uint64_t timeout, std::optional<IDObject<AutoCleanupSemaphore>> semaphoreID, std::optional<IDObject<AutoCleanupFence>> fenceID,
		std::uint32_t& returnIndex, IDObject<WindowPointer> windowID);

protected:
	const LogicalDeviceCoreInternal& _core;

	const DeviceRenderPassDataInternal& _deviceRenderPassData;
	const SharedRenderPassDataInternal& _sharedRenderPassData;

	const DevicePipelineDataInternal& _devicePipelineData;
	const SynchronizationListInternal& _synchronizationList;

	const ImageDataListInternal& _imageList;

	WindowListInternal& _windowList;

	VkDevice _device;
	VkCommandBuffer _buffer;

	VkQueue _queue;
};

export class PrimaryNIRCommandBufferInternal : public AutoCleanUpCommandBuffer
{
public:
	PrimaryNIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
		const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
		const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~PrimaryNIRCommandBufferInternal();

	PrimaryNIRCommandBufferInternal(const PrimaryNIRCommandBufferInternal&) noexcept = delete;
	PrimaryNIRCommandBufferInternal(PrimaryNIRCommandBufferInternal&& rhs) noexcept = delete;

	PrimaryNIRCommandBufferInternal& operator=(const PrimaryNIRCommandBufferInternal&) noexcept = delete;
	PrimaryNIRCommandBufferInternal& operator=(PrimaryNIRCommandBufferInternal&& rhs) noexcept = delete;

	void BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers);
	void EndRenderPass();

	void TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);
	void TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);
};

export class SecondaryNIRCommandBufferInternal : public AutoCleanUpCommandBuffer
{
public:
	SecondaryNIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
		const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
		const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~SecondaryNIRCommandBufferInternal();

	SecondaryNIRCommandBufferInternal(const SecondaryNIRCommandBufferInternal&) noexcept = delete;
	SecondaryNIRCommandBufferInternal(SecondaryNIRCommandBufferInternal&& rhs) noexcept = delete;

	SecondaryNIRCommandBufferInternal& operator=(const SecondaryNIRCommandBufferInternal&) noexcept = delete;
	SecondaryNIRCommandBufferInternal& operator=(SecondaryNIRCommandBufferInternal&& rhs) noexcept = delete;
};

export class PrimaryIRCommandBufferInternal : public PrimaryNIRCommandBufferInternal
{
public:
	PrimaryIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
		const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
		const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~PrimaryIRCommandBufferInternal();

	PrimaryIRCommandBufferInternal(const PrimaryIRCommandBufferInternal&) noexcept = delete;
	PrimaryIRCommandBufferInternal(PrimaryIRCommandBufferInternal&& rhs) noexcept = delete;

	PrimaryIRCommandBufferInternal& operator=(const PrimaryIRCommandBufferInternal&) noexcept = delete;
	PrimaryIRCommandBufferInternal& operator=(PrimaryIRCommandBufferInternal&& rhs) noexcept = delete;

	void BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, std::uint32_t startX, std::uint32_t startY,
		std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues, bool usesSecondaryBuffers);
	void EndRenderPass();

	void ResetCommandBuffer(bool freeResources);

	void TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);
	void TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs, std::uint32_t imagesIndex);
};

export class SecondaryIRCommandBufferInternal : public SecondaryNIRCommandBufferInternal
{
public:
	SecondaryIRCommandBufferInternal(const LogicalDeviceCoreInternal& core, const DeviceRenderPassDataInternal& deviceRenderPassData,
		const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
		const ImageDataListInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~SecondaryIRCommandBufferInternal();

	SecondaryIRCommandBufferInternal(const SecondaryIRCommandBufferInternal&) noexcept = delete;
	SecondaryIRCommandBufferInternal(SecondaryIRCommandBufferInternal&& rhs) noexcept = delete;

	SecondaryIRCommandBufferInternal& operator=(const SecondaryIRCommandBufferInternal&) noexcept = delete;
	SecondaryIRCommandBufferInternal& operator=(SecondaryIRCommandBufferInternal&& rhs) noexcept = delete;

	void ResetCommandBuffer(bool freeResources);
};