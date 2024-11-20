module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandBuffer.Internal;

AutoCleanUpCommandBuffer::AutoCleanUpCommandBuffer(VkDevice device, VkCommandBuffer buffer, VkQueue queue) : _device(device), _buffer(buffer), _queue(queue)
{
}

AutoCleanUpCommandBuffer::~AutoCleanUpCommandBuffer()
{
}

PrimaryNIRCommandBufferInternal::PrimaryNIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue) : AutoCleanUpCommandBuffer(device, buffer, queue)
{
}

PrimaryNIRCommandBufferInternal::~PrimaryNIRCommandBufferInternal()
{
}

SecondaryNIRCommandBufferInternal::SecondaryNIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue) : AutoCleanUpCommandBuffer(device, buffer, queue)
{
}

SecondaryNIRCommandBufferInternal::~SecondaryNIRCommandBufferInternal()
{
}

PrimaryIRCommandBufferInternal::PrimaryIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue) : PrimaryNIRCommandBufferInternal(device, buffer, queue)
{
}

PrimaryIRCommandBufferInternal::~PrimaryIRCommandBufferInternal()
{
}

SecondaryIRCommandBufferInternal::SecondaryIRCommandBufferInternal(VkDevice device, VkCommandBuffer buffer, VkQueue queue) : SecondaryNIRCommandBufferInternal(device, buffer, queue)
{
}

SecondaryIRCommandBufferInternal::~SecondaryIRCommandBufferInternal()
{
}