module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.CommandBuffer.Internal;

import VulkanSimplifiers.CommonCommandBuffer.Data;

export class AutoCleanUpCommandBuffer
{
public:
	AutoCleanUpCommandBuffer(VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~AutoCleanUpCommandBuffer();

	AutoCleanUpCommandBuffer(const AutoCleanUpCommandBuffer&) noexcept = default;
	AutoCleanUpCommandBuffer(AutoCleanUpCommandBuffer&& rhs) noexcept = default;

	AutoCleanUpCommandBuffer& operator=(const AutoCleanUpCommandBuffer&) noexcept = default;
	AutoCleanUpCommandBuffer& operator=(AutoCleanUpCommandBuffer&& rhs) noexcept = default;

	void BeginRecording(CommandBufferUsage usage);
	void EndRecording();

protected:
	VkDevice _device;
	VkCommandBuffer _buffer;

	VkQueue _queue;
};

export class PrimaryNIRCommandBufferInternal : public AutoCleanUpCommandBuffer
{
public:
	PrimaryNIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~PrimaryNIRCommandBufferInternal();

	PrimaryNIRCommandBufferInternal(const PrimaryNIRCommandBufferInternal&) noexcept = default;
	PrimaryNIRCommandBufferInternal(PrimaryNIRCommandBufferInternal&& rhs) noexcept = default;

	PrimaryNIRCommandBufferInternal& operator=(const PrimaryNIRCommandBufferInternal&) noexcept = default;
	PrimaryNIRCommandBufferInternal& operator=(PrimaryNIRCommandBufferInternal&& rhs) noexcept = default;
};

export class SecondaryNIRCommandBufferInternal : public AutoCleanUpCommandBuffer
{
public:
	SecondaryNIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~SecondaryNIRCommandBufferInternal();

	SecondaryNIRCommandBufferInternal(const SecondaryNIRCommandBufferInternal&) noexcept = default;
	SecondaryNIRCommandBufferInternal(SecondaryNIRCommandBufferInternal&& rhs) noexcept = default;

	SecondaryNIRCommandBufferInternal& operator=(const SecondaryNIRCommandBufferInternal&) noexcept = default;
	SecondaryNIRCommandBufferInternal& operator=(SecondaryNIRCommandBufferInternal&& rhs) noexcept = default;
};

export class PrimaryIRCommandBufferInternal : public PrimaryNIRCommandBufferInternal
{
public:
	PrimaryIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~PrimaryIRCommandBufferInternal();

	PrimaryIRCommandBufferInternal(const PrimaryIRCommandBufferInternal&) noexcept = default;
	PrimaryIRCommandBufferInternal(PrimaryIRCommandBufferInternal&& rhs) noexcept = default;

	PrimaryIRCommandBufferInternal& operator=(const PrimaryIRCommandBufferInternal&) noexcept = default;
	PrimaryIRCommandBufferInternal& operator=(PrimaryIRCommandBufferInternal&& rhs) noexcept = default;
};

export class SecondaryIRCommandBufferInternal : public SecondaryNIRCommandBufferInternal
{
public:
	SecondaryIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue);
	~SecondaryIRCommandBufferInternal();

	SecondaryIRCommandBufferInternal(const SecondaryIRCommandBufferInternal&) noexcept = default;
	SecondaryIRCommandBufferInternal(SecondaryIRCommandBufferInternal&& rhs) noexcept = default;

	SecondaryIRCommandBufferInternal& operator=(const SecondaryIRCommandBufferInternal&) noexcept = default;
	SecondaryIRCommandBufferInternal& operator=(SecondaryIRCommandBufferInternal&& rhs) noexcept = default;
};