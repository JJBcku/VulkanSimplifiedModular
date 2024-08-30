export module VulkanData.PipelinesList;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedPipelineData.Data;
export import VulkanSimplifiers.DevicePipelineData.Data;

export struct VulkanPipelineData
{
	IDObject<PipelineViewportData> pipelineViewport;
	IDObject<PipelineScissorData> pipelineScissor;
	IDObject<AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData() = default;

	bool operator==(const IDObject<PipelineViewportData>& rhsPipelineViewport) const;
};

export struct VulkanDataPipelinesList
{
	std::vector<VulkanPipelineData> pipelines;

	std::optional<VulkanPipelineData> currentPipeline;

	VulkanDataPipelinesList() = default;
};