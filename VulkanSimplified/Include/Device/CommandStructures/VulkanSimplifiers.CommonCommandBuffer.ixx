export module VulkanSimplifiers.CommonCommandBuffer;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandBuffer.Internal;
import VulkanSimplifiers.CommonCommandBuffer.Data;
import VulkanSimplifiers.DevicePipelineData.Data;

import VulkanSimplifiers.SynchronizationList.Data;
import VulkanSimplifiers.WindowList.Data;

export class CommonCommandBuffer
{
public:
	CommonCommandBuffer(AutoCleanUpCommandBuffer& ref);
	~CommonCommandBuffer();

	CommonCommandBuffer& operator=(const CommonCommandBuffer&) noexcept = delete;

	void BeginRecording(CommandBufferUsage usage);
	void EndRecording();

	void BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID);

	void Draw(std::uint32_t vertexCount, std::uint32_t instanceCount, std::uint32_t firstVertex, std::uint32_t firstInstance);

	bool AcquireNextImage(std::uint64_t timeout, std::optional<IDObject<AutoCleanupSemaphore>> semaphoreID, std::optional<IDObject<AutoCleanupFence>> fenceID,
		std::uint32_t& returnIndex, IDObject<WindowPointer> windowID);

private:
	AutoCleanUpCommandBuffer& _internal;
};