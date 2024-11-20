module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandBuffer.Internal;

AutoCleanUpCommandBuffer::AutoCleanUpCommandBuffer(VkDevice device, VkCommandBuffer buffer, VkQueue queue) : _device(device), _buffer(buffer), _queue(queue)
{
}

AutoCleanUpCommandBuffer::~AutoCleanUpCommandBuffer()
{
}

void AutoCleanUpCommandBuffer::BeginRecording(CommandBufferUsage usage)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	
	switch (usage)
	{
	case CommandBufferUsage::MULTIPLE_USE_SIMULTANEOUS_USAGE:
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		break;
	case CommandBufferUsage::MULTIPLE_USE_NO_SIMULTANEOUS_USAGE:
		break;
	case CommandBufferUsage::ONE_USE:
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		break;
	default:
		throw std::runtime_error("AutoCleanUpCommandBuffer::BeginRecording Error: Program was giwen an erroneous command buffer usage value!");
	}

	if (vkBeginCommandBuffer(_buffer, &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("AutoCleanUpCommandBuffer::BeginRecording Error: Program failed to begin a command buffer's recording session!");
}

void AutoCleanUpCommandBuffer::EndRecording()
{
	if (vkEndCommandBuffer(_buffer) != VK_SUCCESS)
		throw std::runtime_error("AutoCleanUpCommandBuffer::BeginRecording Error: Program failed to end a command buffer's recording session!");
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