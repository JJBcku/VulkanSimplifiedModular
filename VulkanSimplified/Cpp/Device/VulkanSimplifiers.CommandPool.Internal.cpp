module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandPool.Internal;

NIRCommandPoolInternal::NIRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, VkQueue queue, size_t primaryBufferListInitialCapacity,
	size_t secondaryBufferListInitialCapacity) : _device(device), _commandPool(commandPool), _queue(queue),
	_primaryBufferList(primaryBufferListInitialCapacity), _secondaryBufferList(secondaryBufferListInitialCapacity)
{
}

NIRCommandPoolInternal::~NIRCommandPoolInternal()
{
	if (_device != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(_device, _commandPool, nullptr);
	}
}

NIRCommandPoolInternal::NIRCommandPoolInternal(NIRCommandPoolInternal&& rhs) noexcept : _device(rhs._device), _commandPool(rhs._commandPool), _queue(rhs._queue),
_primaryBufferList(std::move(rhs._primaryBufferList)), _secondaryBufferList(std::move(rhs._secondaryBufferList))
{
	rhs._device = VK_NULL_HANDLE;
	rhs._commandPool = VK_NULL_HANDLE;
	rhs._queue = VK_NULL_HANDLE;
}

NIRCommandPoolInternal& NIRCommandPoolInternal::operator=(NIRCommandPoolInternal&& rhs) noexcept
{
	_device = rhs._device;
	_commandPool = rhs._commandPool;
	_queue = rhs._queue;
	_primaryBufferList = std::move(rhs._primaryBufferList);
	_secondaryBufferList = std::move(rhs._secondaryBufferList);

	rhs._device = VK_NULL_HANDLE;
	rhs._commandPool = VK_NULL_HANDLE;
	rhs._queue = VK_NULL_HANDLE;
	return *this;
}

std::vector<IDObject<PrimaryNIRCommandBufferInternal>> NIRCommandPoolInternal::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<PrimaryNIRCommandBufferInternal>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("NIRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("NIRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_primaryBufferList.AddObject(PrimaryNIRCommandBufferInternal(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}

std::vector<IDObject<SecondaryNIRCommandBufferInternal>> NIRCommandPoolInternal::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<SecondaryNIRCommandBufferInternal>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("NIRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("NIRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_secondaryBufferList.AddObject(SecondaryNIRCommandBufferInternal(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}

IRCommandPoolInternal::IRCommandPoolInternal(VkDevice device, VkCommandPool commandPool, VkQueue queue, size_t primaryBufferListInitialCapacity,
	size_t secondaryBufferListInitialCapacity) : _device(device), _commandPool(commandPool), _queue(queue),
	_primaryBufferList(primaryBufferListInitialCapacity), _secondaryBufferList(secondaryBufferListInitialCapacity)
{
}

IRCommandPoolInternal::~IRCommandPoolInternal()
{
	if (_device != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(_device, _commandPool, nullptr);
	}
}

IRCommandPoolInternal::IRCommandPoolInternal(IRCommandPoolInternal&& rhs) noexcept : _device(rhs._device), _commandPool(rhs._commandPool), _queue(rhs._queue),
_primaryBufferList(std::move(rhs._primaryBufferList)), _secondaryBufferList(std::move(rhs._secondaryBufferList))
{
	rhs._device = VK_NULL_HANDLE;
	rhs._commandPool = VK_NULL_HANDLE;
	rhs._queue = VK_NULL_HANDLE;
}

IRCommandPoolInternal& IRCommandPoolInternal::operator=(IRCommandPoolInternal&& rhs) noexcept
{
	_device = rhs._device;
	_commandPool = rhs._commandPool;
	_queue = rhs._queue;
	_primaryBufferList = std::move(rhs._primaryBufferList);
	_secondaryBufferList = std::move(rhs._secondaryBufferList);

	rhs._device = VK_NULL_HANDLE;
	rhs._commandPool = VK_NULL_HANDLE;
	rhs._queue = VK_NULL_HANDLE;
	return *this;
}

std::vector<IDObject<PrimaryIRCommandBufferInternal>> IRCommandPoolInternal::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<PrimaryIRCommandBufferInternal>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("IRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("IRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_primaryBufferList.AddObject(PrimaryIRCommandBufferInternal(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}

std::vector<IDObject<SecondaryIRCommandBufferInternal>> IRCommandPoolInternal::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<SecondaryIRCommandBufferInternal>> ret;

	if (buffersToAllocate == 0)
		throw std::runtime_error("IRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program tried to allocate zero buffers!");

	ret.reserve(buffersToAllocate);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	allocInfo.commandBufferCount = buffersToAllocate;

	std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

	if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
		throw std::runtime_error("IRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program failed to allocate command buffers!");

	for (auto& buffer : add)
	{
		ret.push_back(_secondaryBufferList.AddObject(SecondaryIRCommandBufferInternal(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}