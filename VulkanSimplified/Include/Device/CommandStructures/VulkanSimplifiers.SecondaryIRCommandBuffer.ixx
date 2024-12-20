export module VulkanSimplifiers.SecondaryIRCommandBuffer;

import VulkanSimplifiers.CommandBuffer.Internal;

export import VulkanSimplifiers.CommonCommandBuffer;

export class SecondaryIRCommandBufferSimplifier : public CommonCommandBuffer
{
public:
	SecondaryIRCommandBufferSimplifier(SecondaryIRCommandBufferInternal& ref);
	~SecondaryIRCommandBufferSimplifier();

	SecondaryIRCommandBufferSimplifier& operator=(const SecondaryIRCommandBufferSimplifier&) noexcept = delete;

	void ResetCommandBuffer(bool freeResources);

private:
	SecondaryIRCommandBufferInternal& _internal;
};