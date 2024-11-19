module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.CommandPool.Internal;

import std;
import ListTemplates.UnsortedList;

export class AutoCleanUpCommandPool
{
public:
	AutoCleanUpCommandPool(VkDevice device, VkCommandPool commandPool, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
	~AutoCleanUpCommandPool();

	AutoCleanUpCommandPool(const AutoCleanUpCommandPool&) noexcept = delete;
	AutoCleanUpCommandPool(AutoCleanUpCommandPool&& rhs) noexcept;

	AutoCleanUpCommandPool& operator=(const AutoCleanUpCommandPool&) noexcept = delete;
	AutoCleanUpCommandPool& operator=(AutoCleanUpCommandPool&& rhs) noexcept;

protected:
	VkDevice _device;
	VkCommandPool _commandPool;

	UnsortedList<std::int64_t> _primaryBufferList;
	UnsortedList<std::int64_t> _secondaryBufferList;
};

export class NIRCommandPoolInternal : public AutoCleanUpCommandPool
{
public:
	NIRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
	~NIRCommandPoolInternal();

	NIRCommandPoolInternal(const NIRCommandPoolInternal&) noexcept = delete;
	NIRCommandPoolInternal(NIRCommandPoolInternal&& rhs) noexcept;

	NIRCommandPoolInternal& operator=(const NIRCommandPoolInternal&) noexcept = delete;
	NIRCommandPoolInternal& operator=(NIRCommandPoolInternal&& rhs) noexcept;
};

export class IRCommandPoolInternal : public AutoCleanUpCommandPool
{
public:
	IRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
	~IRCommandPoolInternal();

	IRCommandPoolInternal(const IRCommandPoolInternal&) noexcept = delete;
	IRCommandPoolInternal(IRCommandPoolInternal&& rhs) noexcept;

	IRCommandPoolInternal& operator=(const IRCommandPoolInternal&) noexcept = delete;
	IRCommandPoolInternal& operator=(IRCommandPoolInternal&& rhs) noexcept;
};