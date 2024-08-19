export module VulkanData.SharedData;

import std;
import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedPipelineData.Data;

export struct VulkanSharedData
{
	IDObject<ShaderSharedPipelineData> _pipelineShaderData;

	VulkanSharedData() = default;
};