export module VulkanSimplifiers.SharedPipelineData.Data;

import std;

export struct ShaderSpecializationElement;
export struct ShaderSharedPipelineData;

export struct VertexBindingDescriptionData;
export struct VertexAttributeDescriptionData;
export struct VertexInputSharedPipelineData;

export struct PipelineInputAssemblyData;
export struct PipelineRasterizationData;
export struct PipelineMultisampleData;

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
