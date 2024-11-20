export module VulkanSimplifiers.NIRCommandPool;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPool.Internal;
import VulkanSimplifiers.NIRCommandPool.Data;

import VulkanSimplifiers.PrimaryNIRCommandBuffer;
import VulkanSimplifiers.SecondaryNIRCommandBuffer;

export class NIRCommandPoolSimplifier
{
public:
	NIRCommandPoolSimplifier(NIRCommandPoolInternal& ref);
	~NIRCommandPoolSimplifier();

	NIRCommandPoolSimplifier(const NIRCommandPoolSimplifier&) noexcept = default;
	NIRCommandPoolSimplifier(NIRCommandPoolSimplifier&&) noexcept = default;

	NIRCommandPoolSimplifier& operator=(const NIRCommandPoolSimplifier&) noexcept = delete;
	NIRCommandPoolSimplifier& operator=(NIRCommandPoolSimplifier&&) noexcept = delete;

	std::vector<IDObject<PrimaryNIRCommandBufferInternal>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);
	std::vector<IDObject<SecondaryNIRCommandBufferInternal>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);

	PrimaryNIRCommandBufferSimplifier GetPrimaryCommandBufferSimplifier(IDObject<PrimaryNIRCommandBufferInternal> bufferID);
	SecondaryNIRCommandBufferSimplifier GetSecondaryCommandBufferSimplifier(IDObject<SecondaryNIRCommandBufferInternal> bufferID);

	const PrimaryNIRCommandBufferSimplifier GetPrimaryCommandBufferSimplifier(IDObject<PrimaryNIRCommandBufferInternal> bufferID) const;
	const SecondaryNIRCommandBufferSimplifier GetSecondaryCommandBufferSimplifier(IDObject<SecondaryNIRCommandBufferInternal> bufferID) const;

private:
	NIRCommandPoolInternal& _internal;
};