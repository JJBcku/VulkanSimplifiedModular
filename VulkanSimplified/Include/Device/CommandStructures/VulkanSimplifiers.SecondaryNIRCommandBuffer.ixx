export module VulkanSimplifiers.SecondaryNIRCommandBuffer;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

export class SecondaryNIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	SecondaryNIRCommandBufferSimplifier(SecondaryNIRCommandBufferInternal& ref);
	~SecondaryNIRCommandBufferSimplifier();

	SecondaryNIRCommandBufferSimplifier& operator=(const SecondaryNIRCommandBufferSimplifier&) noexcept = delete;

private:
	SecondaryNIRCommandBufferInternal& _internal;
};