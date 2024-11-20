export module VulkanSimplifiers.CommonCommandBuffer;

import VulkanSimplifiers.CommandBuffer.Internal;
import VulkanSimplifiers.CommonCommandBuffer.Data;

export class CommonCommandBuffer
{
public:
	CommonCommandBuffer(AutoCleanUpCommandBuffer& ref);
	~CommonCommandBuffer();

	CommonCommandBuffer& operator=(const CommonCommandBuffer&) noexcept = delete;

	void BeginRecording(CommandBufferUsage usage);
	void EndRecording();

private:
	AutoCleanUpCommandBuffer& _internal;
};