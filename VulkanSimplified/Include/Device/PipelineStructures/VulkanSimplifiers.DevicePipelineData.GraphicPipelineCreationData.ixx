export module VulkanSimplifiers.DevicePipelineData.GraphicPipelineCreationData;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.DevicePipelineData.Data;
export import VulkanSimplifiers.SharedPipelineData.Data;
export import VulkanSimplifiers.DeviceRenderPassData.Data;
export import VulkanSimplifiers.ShaderList.Data;

export enum class PipelineDerrivationSettings : std::uint64_t
{
	DO_NOT_DERRIVE = 0,
	PIPELINE_ID = 1,
	PIPELINE_INDEX = 2,
};

export union GraphicPipelineDerrivationData
{
	PipelineDerrivationSettings settings;

	struct
	{
		PipelineDerrivationSettings settings;
		IDObject<AutoCleanupGraphicsPipeline> ID;
	} pipelineID;

	struct
	{
		PipelineDerrivationSettings settings;
		size_t index;
	} pipelineIndex;

	GraphicPipelineDerrivationData();
};

export struct ShaderSpecializationData
{
	std::vector<IDObject<ShaderSpecializationElement>> specializationElements;
	size_t dataSize;
	const void* data;

	ShaderSpecializationData();
};

export struct ShaderStageData
{
	IDObject<ShaderSharedPipelineData> sharedData;
	ArbitraryShaderID shaderDeviceID;

	std::optional<ShaderSpecializationData> specializationData;

	ShaderStageData() = default;
};

export struct ViewportStatePipelineDataPoint
{
	IDObject<PipelineViewportData> viewport;
	IDObject<PipelineScissorData> scissor;

	ViewportStatePipelineDataPoint() = default;
};

export struct GraphicPipelineCreationData
{
	std::vector<ShaderStageData> shaderStages;
	IDObject<VertexInputSharedPipelineData> vertexInputData;
	IDObject<PipelineInputAssemblyData> inputAssemblyData;
	std::vector<ViewportStatePipelineDataPoint> viewportData;
	IDObject<PipelineRasterizationData> rasterizationData;
	IDObject<PipelineMultisampleData> samplingData;
	std::optional<IDObject<PipelineDepthStencilStateData>> depthStencilData;
	std::vector<IDObject<PipelineColorBlendAttachment>> colorBlendingData;

	IDObject<AutoCleanupPipelineLayout> pipelineLayout;
	IDObject<AutoCleanupRenderPass> renderPass;
	std::uint32_t subpassIndex;
	std::uint32_t padding;
	GraphicPipelineDerrivationData pipelineDerrivationData;

	GraphicPipelineCreationData();
};