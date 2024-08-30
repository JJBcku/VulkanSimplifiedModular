module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedPipelineData.InternalData;

import std;
export import ListTemplates.IDObject;

export struct ShaderSpecializationElement
{
	std::uint32_t ID;
	std::uint32_t offset;
	size_t size;

	ShaderSpecializationElement();

	bool operator==(const ShaderSpecializationElement& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const ShaderSpecializationElement& rhs) const noexcept = default;
};

export struct ShaderSharedPipelineData
{
	VkShaderStageFlagBits shaderStages;
	std::uint32_t padding;
	std::string entryPointName;

	ShaderSharedPipelineData();

	bool operator==(const ShaderSharedPipelineData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const ShaderSharedPipelineData& rhs) const noexcept = default;
};

export struct VertexAttributeDescriptionData
{
	VkFormat format;
	std::uint32_t offset;

	VertexAttributeDescriptionData();

	bool operator==(const VertexAttributeDescriptionData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const VertexAttributeDescriptionData& rhs) const noexcept = default;
};

export struct VertexBindingDescriptionData
{
	std::uint32_t stride;
	VkVertexInputRate inputRate;

	std::vector<IDObject<VertexAttributeDescriptionData>> vertexAttributes;

	VertexBindingDescriptionData();

	bool operator==(const VertexBindingDescriptionData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const VertexBindingDescriptionData& rhs) const noexcept = default;
};

export struct VertexInputSharedPipelineData
{
	std::vector<IDObject<VertexBindingDescriptionData>> vertexBindings;

	VertexInputSharedPipelineData() = default;

	bool operator==(const VertexInputSharedPipelineData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const VertexInputSharedPipelineData& rhs) const noexcept = default;
};

export struct PipelineViewportData
{
	float startX;
	float startY;
	float width;
	float height;
	float minDepth;
	float maxDepth;

	PipelineViewportData();

	bool operator==(const PipelineViewportData& rhs) const noexcept = default;
	std::partial_ordering operator<=>(const PipelineViewportData& rhs) const noexcept = default;
};

export struct PipelineScissorData
{
	std::int32_t offsetX;
	std::int32_t offsetY;
	std::uint32_t width;
	std::uint32_t height;

	PipelineScissorData();

	bool operator==(const PipelineScissorData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const PipelineScissorData& rhs) const noexcept = default;
};

export struct PipelineInputAssemblyData
{
	VkPrimitiveTopology topology;
	VkBool32 primitiveRestartEnable;

	PipelineInputAssemblyData();

	bool operator==(const PipelineInputAssemblyData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const PipelineInputAssemblyData& rhs) const noexcept = default;
};

export struct PipelineRasterizationData
{
	VkPolygonMode polygonMode;
	VkCullModeFlagBits cullMode;
	VkFrontFace frontFace;
	std::uint32_t padding;

	PipelineRasterizationData();

	bool operator==(const PipelineRasterizationData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const PipelineRasterizationData& rhs) const noexcept = default;
};

export struct PipelineMultisampleData
{
	VkSampleCountFlagBits sampleCount;
	VkBool32 sampleShadingEnable;
	float minSampleShading;
	std::uint32_t padding;

	PipelineMultisampleData();

	bool operator==(const PipelineMultisampleData& rhs) const noexcept = default;
	std::partial_ordering operator<=>(const PipelineMultisampleData& rhs) const noexcept = default;
};

export struct PipelineDepthStencilStateData
{
	VkBool32 depthTestEnable;
	VkBool32 depthWriteEnable;
	VkCompareOp compareOp;
	float minDepth;
	float maxDepth;
	std::uint32_t padding;

	PipelineDepthStencilStateData();

	bool operator==(const PipelineDepthStencilStateData& rhs) const noexcept = default;
	std::partial_ordering operator<=>(const PipelineDepthStencilStateData& rhs) const noexcept = default;
};

export struct PipelineColorBlendAttachment
{
	VkBool32 blendEnable;
	VkBlendFactor srcColorBlend;
	VkBlendFactor dstColorBlend;
	VkBlendOp colorBlendOp;
	VkBlendFactor srcAlphaBlend;
	VkBlendFactor dstAlphaBlend;
	VkBlendOp alphaBlendOp;
	VkColorComponentFlags colorWriteMask;

	PipelineColorBlendAttachment();

	bool operator==(const PipelineColorBlendAttachment& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const PipelineColorBlendAttachment& rhs) const noexcept = default;
};

export struct PushConstantData
{
	VkShaderStageFlags shaderStages;
	std::uint32_t offset;
	std::uint32_t size;
	std::uint32_t padding;

	PushConstantData();

	bool operator==(const PushConstantData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const PushConstantData& rhs) const noexcept = default;
};