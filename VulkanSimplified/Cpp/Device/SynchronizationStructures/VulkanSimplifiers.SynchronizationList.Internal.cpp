module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SynchronizationList.Internal;

SynchronizationListInternal::SynchronizationListInternal(VkDevice device, const SynchronizationListCreationData& createInfo) : _device(device),
	_fenceList(createInfo.fenceListInitialCapacity), _semaphoreList(createInfo.semaphoreListInitialCapacity)
{
}

SynchronizationListInternal::~SynchronizationListInternal()
{
}

IDObject<AutoCleanupFence> SynchronizationListInternal::AddFence(bool createSignaled, size_t addOnReserve)
{
	VkFenceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	
	if (createSignaled)
		createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	VkFence add = VK_NULL_HANDLE;

	if (vkCreateFence(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("SynchronizationListInternal::AddFence Error: Program failed to create a fence!");

	return _fenceList.AddObject(AutoCleanupFence(_device, add), addOnReserve);
}

VkFence SynchronizationListInternal::GetFence(IDObject<AutoCleanupFence> fenceIDs) const
{
	return _fenceList.GetConstObject(fenceIDs).GetFence();
}

bool SynchronizationListInternal::WaitOnFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs, bool waitForAll, std::uint64_t timeout)
{
	if (fenceIDs.empty())
		throw std::runtime_error("SynchronizationListInternal::WaitOnFences Error: Program tried to wait on no fences!");

	if (timeout == 0)
		throw std::runtime_error("SynchronizationListInternal::WaitOnFences Error: Timeout cannot be zero!");

	std::vector<VkFence> fences;
	fences.reserve(fenceIDs.size());

	for (size_t i = 0; i < fenceIDs.size(); ++i)
	{
		fences.push_back(GetFence(fenceIDs[i]));
	}

	VkBool32 waitAll = VK_FALSE;
	if (waitForAll)
		waitAll = VK_TRUE;

	VkResult result = vkWaitForFences(_device, static_cast<std::uint32_t>(fences.size()), fences.data(), waitAll, timeout);

	if (result != VK_SUCCESS && result != VK_TIMEOUT)
		throw std::runtime_error("SynchronizationListInternal::WaitOnFences Error: Program failed to wait on fences!");

	return result == VK_SUCCESS;
}

void SynchronizationListInternal::ResetFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs)
{
	if (fenceIDs.empty())
		throw std::runtime_error("SynchronizationListInternal::ResetFence Error: Program tried to reset no fences!");

	std::vector<VkFence> fences;
	fences.reserve(fenceIDs.size());

	for (size_t i = 0; i < fenceIDs.size(); ++i)
	{
		fences.push_back(GetFence(fenceIDs[i]));
	}

	if (vkResetFences(_device, static_cast<std::uint32_t>(fences.size()), fences.data()) != VK_SUCCESS)
		throw std::runtime_error("SynchronizationListInternal::ResetFence Error: Program failed to reset the fences!");
}

IDObject<AutoCleanupSemaphore> SynchronizationListInternal::AddSemaphore(size_t addOnReserve)
{
	VkSemaphoreCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkSemaphore add = VK_NULL_HANDLE;

	if (vkCreateSemaphore(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("SynchronizationListInternal::AddSemaphore Error: Program failed to create a semaphore!");

	return _semaphoreList.AddObject(AutoCleanupSemaphore(_device, add), addOnReserve);
}

VkSemaphore SynchronizationListInternal::GetSemaphore(IDObject<AutoCleanupSemaphore> semaphoreID) const
{
	return _semaphoreList.GetConstObject(semaphoreID).GetSemaphore();
}