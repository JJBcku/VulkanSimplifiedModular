export module VulkanSimplifiers.PrimaryIRCommandBuffer;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

export class PrimaryIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	PrimaryIRCommandBufferSimplifier(PrimaryIRCommandBufferInternal& ref);
	~PrimaryIRCommandBufferSimplifier();

	PrimaryIRCommandBufferSimplifier& operator=(const PrimaryIRCommandBufferSimplifier&) noexcept = delete;

private:
	PrimaryIRCommandBufferInternal& _internal;
};