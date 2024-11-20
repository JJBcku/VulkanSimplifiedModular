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

std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> NIRCommandPoolInternal::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> ret;

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
		ret.push_back(_primaryBufferList.AddObject(std::make_unique<PrimaryNIRCommandBufferInternal>(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}

std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> NIRCommandPoolInternal::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> ret;

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
		ret.push_back(_secondaryBufferList.AddObject(std::make_unique<SecondaryNIRCommandBufferInternal>(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}

PrimaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID)
{
	return *_primaryBufferList.GetObject(bufferID);
}

SecondaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID)
{
	return *_secondaryBufferList.GetObject(bufferID);
}

const PrimaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID) const
{
	return *_primaryBufferList.GetConstObject(bufferID);
}

const SecondaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID) const
{
	return *_secondaryBufferList.GetConstObject(bufferID);
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

std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> IRCommandPoolInternal::AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> ret;

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
		ret.push_back(_primaryBufferList.AddObject(std::make_unique<PrimaryIRCommandBufferInternal>(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}

std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> IRCommandPoolInternal::AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve)
{
	std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> ret;

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
		ret.push_back(_secondaryBufferList.AddObject(std::make_unique<SecondaryIRCommandBufferInternal>(_device, buffer, _queue), addOnReserve));
	}

	return ret;
}

PrimaryIRCommandBufferInternal& IRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID)
{
	return *_primaryBufferList.GetObject(bufferID);
}

SecondaryIRCommandBufferInternal& IRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID)
{
	return *_secondaryBufferList.GetObject(bufferID);
}

const PrimaryIRCommandBufferInternal& IRCommandPoolInternal::GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID) const
{
	return *_primaryBufferList.GetConstObject(bufferID);
}

const SecondaryIRCommandBufferInternal& IRCommandPoolInternal::GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID) const
{
	return *_secondaryBufferList.GetConstObject(bufferID);
}