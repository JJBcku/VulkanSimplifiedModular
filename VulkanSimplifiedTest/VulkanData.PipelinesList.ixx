export module VulkanData.PipelinesList;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedPipelineData.Data;
export import VulkanSimplifiers.DevicePipelineData.Data;
export import VulkanSimplifiers.ImageDataList.Data;

export struct VulkanPipelineData
{
	IDObject<PipelineViewportData> pipelineViewport;
	IDObject<PipelineScissorData> pipelineScissor;
	IDObject<AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData() = default;

	bool operator==(const IDObject<PipelineViewportData>& rhsPipelineViewport) const;
};

export struct VulkanAttachmentData
{
	std::uint32_t width;
	std::uint32_t height;

	IDObject<AutoCleanup2DImage> colorAttachmentImage;

	VulkanAttachmentData();
};

export struct VulkanDataPipelinesList
{
	std::vector<VulkanPipelineData> pipelines;

	std::optional<VulkanPipelineData> currentPipeline;

	std::optional<VulkanAttachmentData> attachmentData;

	VulkanDataPipelinesList() = default;
};