export module VulkanData.PipelinesList;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedPipelineData.Data;

export struct VulkanPipelineData
{
	IDObject<PipelineViewportData> pipelineViewport;
	IDObject<PipelineScissorData> pipelineScissor;

	VulkanPipelineData() = default;

	bool operator==(const IDObject<PipelineViewportData>& rhsPipelineViewport);
};

export struct VulkanDataPipelinesList
{
	std::vector<VulkanPipelineData> stump;

	VulkanDataPipelinesList() = default;
};