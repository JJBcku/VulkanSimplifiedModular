export module VulkanSimplifiers.CommonCommandBuffer;

import VulkanSimplifiers.CommandBuffer.Internal;

export class CommonCommandBuffer
{
public:
	CommonCommandBuffer(AutoCleanUpCommandBuffer& ref);
	~CommonCommandBuffer();

	CommonCommandBuffer& operator=(const CommonCommandBuffer&) noexcept = delete;

private:
	AutoCleanUpCommandBuffer& _internal;
};