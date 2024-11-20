module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandPoolList.Internal;

CommandPoolListInternal::CommandPoolListInternal(const LogicalDeviceCoreInternal& deviceCore, const CommandPoolListCreationData& creationData) : _deviceCore(deviceCore),
	_device(deviceCore.GetDevice()), _noIndividualResetCommandPoolList(creationData.noIndividualResetCommandPoolListInitialReservation),
	_individualResetCommandPoolList(creationData.individualResetCommandPoolListInitialReservation)
{
}

CommandPoolListInternal::~CommandPoolListInternal()
{
}

IDObject<NIRCommandPoolInternal> CommandPoolListInternal::AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	VkCommandPoolCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.queueFamilyIndex = _deviceCore.GetQueueFamily(queueID);

	if (frequentlyRedoneBuffers)
		createInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	VkCommandPool add = VK_NULL_HANDLE;

	if (vkCreateCommandPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("CommandPoolListInternal::AddCommandPoolWithoutIndividualReset Error: Program failed to create a command pool!");

	return _noIndividualResetCommandPoolList.AddObject(NIRCommandPoolInternal(_device, add, _deviceCore.GetQueue(queueID), primaryBufferListInitialCapacity,
		secondaryBufferListInitialCapacity), addOnReserve);
}

IDObject<IRCommandPoolInternal> CommandPoolListInternal::AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
	size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserve)
{
	VkCommandPoolCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.queueFamilyIndex = _deviceCore.GetQueueFamily(queueID);
	createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	if (frequentlyRedoneBuffers)
		createInfo.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	VkCommandPool add = VK_NULL_HANDLE;

	if (vkCreateCommandPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("CommandPoolListInternal::AddCommandPoolWithIndividualReset Error: Program failed to create a command pool!");

	return _individualResetCommandPoolList.AddObject(IRCommandPoolInternal(_device, add, _deviceCore.GetQueue(queueID), primaryBufferListInitialCapacity,
		secondaryBufferListInitialCapacity), addOnReserve);
}

NIRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<NIRCommandPoolInternal> poolID)
{
	return _noIndividualResetCommandPoolList.GetObject(poolID);
}

IRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithIndividualResetSimplifier(IDObject<IRCommandPoolInternal> poolID)
{
	return _individualResetCommandPoolList.GetObject(poolID);
}

const NIRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithoutIndividualResetSimplifier(IDObject<NIRCommandPoolInternal> poolID) const
{
	return _noIndividualResetCommandPoolList.GetConstObject(poolID);
}

const IRCommandPoolInternal& CommandPoolListInternal::GetCommandPoolWithIndividualResetSimplifier(IDObject<IRCommandPoolInternal> poolID) const
{
	return _individualResetCommandPoolList.GetConstObject(poolID);
}