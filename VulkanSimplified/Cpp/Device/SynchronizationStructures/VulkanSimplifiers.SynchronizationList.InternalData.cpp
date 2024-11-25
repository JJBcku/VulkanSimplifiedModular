module;

#include <vulkan\vulkan.hpp>

module VulkanSimplifiers.SynchronizationList.InternalData;

AutoCleanupFence::AutoCleanupFence(VkDevice device, VkFence fence) : _device(device), _fence(fence)
{
}

AutoCleanupFence::~AutoCleanupFence()
{
	DestroyFence();
}

AutoCleanupFence::AutoCleanupFence(AutoCleanupFence&& rhs) noexcept : _device(rhs._device), _fence(rhs._fence)
{
	rhs._device = VK_NULL_HANDLE;
	rhs._fence = VK_NULL_HANDLE;
}

AutoCleanupFence& AutoCleanupFence::operator=(AutoCleanupFence&& rhs) noexcept
{
	DestroyFence();
	_device = rhs._device;
	_fence = rhs._fence;

	rhs._device = VK_NULL_HANDLE;
	rhs._fence = VK_NULL_HANDLE;
	return *this;
}

VkFence AutoCleanupFence::GetFence() const
{
	return _fence;
}

void AutoCleanupFence::DestroyFence()
{
	if (_fence != VK_NULL_HANDLE)
	{
		vkDestroyFence(_device, _fence, nullptr);
		_fence = VK_NULL_HANDLE;
	}
}