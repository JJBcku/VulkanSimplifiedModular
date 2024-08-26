export module VulkanData.PipelinesList;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedPipelineData.Data;

export struct VulkanPipelineData
{
	IDObject<PipelineViewportData> pipelineViewport;
	IDObject<PipelineScissorData> pipelineScissor;

	VulkanPipelineData() = default;

	bool operator==(const IDObject<PipelineViewportData>& rhsPipelineViewport) const;
};

export struct VulkanDataPipelinesList
{
	std::vector<VulkanPipelineData> pipelines;

	std::optional<VulkanPipelineData> currentPipeline;

	VulkanDataPipelinesList() = default;
};