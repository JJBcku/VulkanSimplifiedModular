export module VulkanData.PipelineLayoutData;

import std;
export import ListTemplates.IDObject;

import VulkanSimplifiers.DevicePipelineData.Data;

export struct VulkanPipelineLayoutData
{
	IDObject<AutoCleanupPipelineLayout> pipelineLayout;

	VulkanPipelineLayoutData() = default;
};