export module VulkanSimplifiers.SharedPipelineData.Data;

import std;

export struct ShaderSpecializationElement;
export struct ShaderSharedPipelineData;
export struct VertexBindingDescriptionData;
export struct VertexAttributeDescriptionData;
export struct VertexInputSharedPipelineData;

export enum class VertexBindingInputRate : std::uint64_t
{
	VERTEX = 1,
	INSTANCE = 2,
};