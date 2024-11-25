export module VulkanSimplifiers.CommonCommandBuffer;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandBuffer.Internal;
import VulkanSimplifiers.CommonCommandBuffer.Data;
import VulkanSimplifiers.DevicePipelineData.Data;

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

private:
	AutoCleanUpCommandBuffer& _internal;
};