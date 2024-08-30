export module VulkanData.SharedData;

import std;
import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedPipelineData.Data;

export struct VulkanSharedData
{
	IDObject<ShaderSharedPipelineData> _pipelineVertexShaderData;
	IDObject<ShaderSharedPipelineData> _pipelineFragmentShaderData;

	IDObject<VertexInputSharedPipelineData> _vertexInputData;
	IDObject<PipelineInputAssemblyData> _pipelineInputAssembly;
	IDObject<PipelineRasterizationData> _pipelineRasterizationAssembly;
	IDObject<PipelineMultisampleData> _pipelineMultisampling;
	IDObject<PipelineColorBlendAttachment> _pipelineColorBlendAttachment;

	VulkanSharedData() = default;
};