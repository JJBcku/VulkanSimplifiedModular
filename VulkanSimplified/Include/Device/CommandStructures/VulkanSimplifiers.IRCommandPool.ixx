export module VulkanSimplifiers.IRCommandPool;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPool.Internal;
import VulkanSimplifiers.IRCommandPool.Data;

import VulkanSimplifiers.PrimaryIRCommandBuffer;
import VulkanSimplifiers.SecondaryIRCommandBuffer;

export class IRCommandPoolSimplifier
{
public:
	IRCommandPoolSimplifier(IRCommandPoolInternal& ref);
	~IRCommandPoolSimplifier();

	IRCommandPoolSimplifier& operator=(const IRCommandPoolSimplifier&) noexcept = delete;

	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);
	std::vector<IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);

	PrimaryIRCommandBufferSimplifier GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID);
	SecondaryIRCommandBufferSimplifier GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID);

	const PrimaryIRCommandBufferSimplifier GetPrimaryCommandBufferSimplifier(IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>> bufferID) const;
	const SecondaryIRCommandBufferSimplifier GetSecondaryCommandBufferSimplifier(IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>> bufferID) const;

private:
	IRCommandPoolInternal& _internal;
};