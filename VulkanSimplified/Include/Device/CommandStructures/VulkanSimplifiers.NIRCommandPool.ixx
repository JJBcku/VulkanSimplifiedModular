export module VulkanSimplifiers.NIRCommandPool;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPool.Internal;
import VulkanSimplifiers.NIRCommandPool.Data;

import VulkanSimplifiers.PrimaryNIRCommandBuffer;
import VulkanSimplifiers.SecondaryNIRCommandBuffer;

import VulkanSimplifiers.SynchronizationList.Data;
import VulkanSimplifiers.WindowList.Data;

export class NIRCommandPoolSimplifier
{
public:
	NIRCommandPoolSimplifier(NIRCommandPoolInternal& ref);
	~NIRCommandPoolSimplifier();

	NIRCommandPoolSimplifier(const NIRCommandPoolSimplifier&) noexcept = default;
	NIRCommandPoolSimplifier(NIRCommandPoolSimplifier&&) noexcept = default;

	NIRCommandPoolSimplifier& operator=(const NIRCommandPoolSimplifier&) noexcept = delete;
	NIRCommandPoolSimplifier& operator=(NIRCommandPoolSimplifier&&) noexcept = delete;

	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);
	std::vector<IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);

	PrimaryNIRCommandBufferSimplifier GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID);
	SecondaryNIRCommandBufferSimplifier GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID);

	const PrimaryNIRCommandBufferSimplifier GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>> bufferID) const;
	const SecondaryNIRCommandBufferSimplifier GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>> bufferID) const;

	void ResetCommandPool(bool freeResources);

	bool PresentSwapchainToQueue(IDObject<WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs, std::uint32_t imageIndex);

private:
	NIRCommandPoolInternal& _internal;
};