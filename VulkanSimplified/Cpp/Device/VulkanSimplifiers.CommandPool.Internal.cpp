module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandPool.Internal;

AutoCleanUpCommandPool::AutoCleanUpCommandPool(VkDevice device, VkCommandPool commandPool, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity) :
	_device(device), _commandPool(commandPool), _primaryBufferList(primaryBufferListInitialCapacity), _secondaryBufferList(secondaryBufferListInitialCapacity)
{
}

AutoCleanUpCommandPool::~AutoCleanUpCommandPool()
{
	if (_device != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(_device, _commandPool, nullptr);
	}
}

AutoCleanUpCommandPool::AutoCleanUpCommandPool(AutoCleanUpCommandPool&& rhs) noexcept : _device(rhs._device), _commandPool(rhs._commandPool),
_primaryBufferList(std::move(rhs._primaryBufferList)), _secondaryBufferList(std::move(rhs._secondaryBufferList))
{
	rhs._device = VK_NULL_HANDLE;
	rhs._commandPool = VK_NULL_HANDLE;
}

AutoCleanUpCommandPool& AutoCleanUpCommandPool::operator=(AutoCleanUpCommandPool&& rhs) noexcept
{
	_device = rhs._device;
	_commandPool = rhs._commandPool;
	_primaryBufferList = std::move(rhs._primaryBufferList);
	_secondaryBufferList = std::move(rhs._secondaryBufferList);

	rhs._device = VK_NULL_HANDLE;
	rhs._commandPool = VK_NULL_HANDLE;
	return *this;
}

NIRCommandPoolInternal::NIRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, size_t primaryBufferListInitialCapacity,
	size_t secondaryBufferListInitialCapacity) : AutoCleanUpCommandPool(device, commandPool, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity)
{
}

NIRCommandPoolInternal::~NIRCommandPoolInternal()
{
}

NIRCommandPoolInternal::NIRCommandPoolInternal(NIRCommandPoolInternal&& rhs) noexcept :
	AutoCleanUpCommandPool(std::move(rhs))
{
}

NIRCommandPoolInternal& NIRCommandPoolInternal::operator=(NIRCommandPoolInternal&& rhs) noexcept
{
	*static_cast<AutoCleanUpCommandPool*>(this) = static_cast<AutoCleanUpCommandPool>(std::move(rhs));
	return *this;
}

IRCommandPoolInternal::IRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, size_t primaryBufferListInitialCapacity,
	size_t secondaryBufferListInitialCapacity) : AutoCleanUpCommandPool(device, commandPool, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity)
{
}

IRCommandPoolInternal::~IRCommandPoolInternal()
{
}

IRCommandPoolInternal::IRCommandPoolInternal(IRCommandPoolInternal&& rhs) noexcept :
	AutoCleanUpCommandPool(std::move(rhs))
{
}

IRCommandPoolInternal& IRCommandPoolInternal::operator=(IRCommandPoolInternal&& rhs) noexcept
{
	*static_cast<AutoCleanUpCommandPool*>(this) = static_cast<AutoCleanUpCommandPool>(std::move(rhs));
	return *this;
}