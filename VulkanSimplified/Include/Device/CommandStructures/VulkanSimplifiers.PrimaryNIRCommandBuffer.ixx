export module VulkanSimplifiers.PrimaryNIRCommandBuffer;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

export class PrimaryNIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	PrimaryNIRCommandBufferSimplifier(PrimaryNIRCommandBufferInternal& ref);
	~PrimaryNIRCommandBufferSimplifier();

	PrimaryNIRCommandBufferSimplifier& operator=(const PrimaryNIRCommandBufferSimplifier&) noexcept = delete;

private:
	PrimaryNIRCommandBufferInternal& _internal;
};