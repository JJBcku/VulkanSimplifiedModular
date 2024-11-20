export module VulkanSimplifiers.IRCommandPool;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPool.Internal;
import VulkanSimplifiers.IRCommandPool.Data;

export class IRCommandPoolSimplifier
{
public:
	IRCommandPoolSimplifier(IRCommandPoolInternal& ref);
	~IRCommandPoolSimplifier();

	IRCommandPoolSimplifier& operator=(const IRCommandPoolSimplifier&) noexcept = delete;

	std::vector<IDObject<PrimaryIRCommandBufferInternal>> AllocatePrimaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);
	std::vector<IDObject<SecondaryIRCommandBufferInternal>> AllocateSecondaryCommandBuffers(std::uint32_t buffersToAllocate, size_t addOnReserve = 0);

private:
	IRCommandPoolInternal& _internal;
};