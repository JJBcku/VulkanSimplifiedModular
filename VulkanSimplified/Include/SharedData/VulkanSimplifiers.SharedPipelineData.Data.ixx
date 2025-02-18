export module VulkanSimplifiers.SharedPipelineData.Data;

import std;

export struct ShaderSpecializationElement;
export struct ShaderSharedPipelineData;

export struct VertexBindingDescriptionData;
export struct VertexAttributeDescriptionData;
export struct VertexInputSharedPipelineData;

export struct PipelineViewportData;
export struct PipelineScissorData;

export struct PipelineInputAssemblyData;
export struct PipelineRasterizationData;
export struct PipelineMultisampleData;
export struct PipelineDepthStencilStateData;
export struct PipelineColorBlendAttachment;

export struct PushConstantData;

export enum class VertexBindingInputRate : std::uint64_t
{
	VERTEX = 1,
	INSTANCE = 2,
};

export enum class PipelinePrimitiveTopology : std::uint64_t
{
	POINT_LIST = 0,
	LINE_LIST = 1,
	LINE_STRIP = 2,
	TRIANGLE_LIST = 3,
	TRIANGLE_STRIP = 4,
	TRIANGLE_FAN = 5,
	LINE_LIST_WITH_ADJACENCY = 6,
	LINE_STRIP_WITH_ADJACENCY = 7,
	TRIANGLE_LIST_WITH_ADJACENCY = 8,
	TRIANGLE_STRIP_WITH_ADJACENCY = 9,
	PATCH_LIST = 10,
};

export enum class PipelinePolygonMode : std::uint64_t
{
	FILL = 1,
	LINE = 2,
	POINT = 3,
};

export enum class DepthUsage : std::uint64_t
{
	TEST = 1,
	WRITE = 2,
	TEST_AND_WRITE = 3,
};

export typedef std::uint64_t ColorBlendingComponentFlags;

export enum ColorBlendingComponentBits : ColorBlendingComponentFlags
{
	COLOR_COMPONENT_R = 0x1,
	COLOR_COMPONENT_G = 0x2,
	COLOR_COMPONENT_B = 0x4,
	COLOR_COMPONENT_A = 0x8,
};

export enum class ColorBlendingPreset : std::uint64_t
{
	NO_BLENDING = 1,
	ALPHA_BLENDING = 2,
	ADDITIVE_BLENDING = 3,
};
