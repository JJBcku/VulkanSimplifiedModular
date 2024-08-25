export module VulkanData.PipelinesList;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedPipelineData.Data;

export struct VulkanPipelineData
{
	IDObject<PipelineViewportData> _pipelineViewport;

	VulkanPipelineData() = default;

	bool operator==(const IDObject<PipelineViewportData>& pipelineViewport);
};

export struct VulkanDataPipelinesList
{
	std::vector<VulkanPipelineData> stump;

	VulkanDataPipelinesList() = default;
};