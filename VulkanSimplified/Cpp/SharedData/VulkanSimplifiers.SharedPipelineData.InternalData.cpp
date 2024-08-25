module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SharedPipelineData.InternalData;

ShaderSpecializationElement::ShaderSpecializationElement()
{
	ID = std::numeric_limits<std::uint32_t>::max();
	offset = std::numeric_limits<std::uint32_t>::max();
	size  = std::numeric_limits<size_t>::max();
}

VertexBindingDescriptionData::VertexBindingDescriptionData()
{
	stride = std::numeric_limits<std::uint32_t>::max();
	inputRate = static_cast<VkVertexInputRate>(std::numeric_limits<std::uint32_t>::max());
}

VertexAttributeDescriptionData::VertexAttributeDescriptionData()
{
	format = VK_FORMAT_UNDEFINED;
	offset = std::numeric_limits<std::uint32_t>::max();
}

PipelineViewportData::PipelineViewportData()
{
	startX = std::numeric_limits<float>::max();
	startY = std::numeric_limits<float>::max();
	width = 0.0f;
	height = 0.0f;
	minDepth = std::numeric_limits<float>::max();
	maxDepth = std::numeric_limits<float>::lowest();
}

PipelineInputAssemblyData::PipelineInputAssemblyData()
{
	topology = static_cast<VkPrimitiveTopology>(std::numeric_limits<std::uint32_t>::max());
	primitiveRestartEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
}

PipelineRasterizationData::PipelineRasterizationData()
{
	polygonMode = static_cast<VkPolygonMode>(std::numeric_limits<std::uint32_t>::max());
	cullMode = static_cast<VkCullModeFlagBits>(std::numeric_limits<std::uint32_t>::max());
	frontFace = static_cast<VkFrontFace>(std::numeric_limits<std::uint32_t>::max());
	padding = 0;
}

PipelineMultisampleData::PipelineMultisampleData()
{
	sampleCount = static_cast<VkSampleCountFlagBits>(std::numeric_limits<std::uint32_t>::max());
	sampleShadingEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
	minSampleShading = std::numeric_limits<float>::max();
	padding = 0;
}

PipelineDepthStencilStateData::PipelineDepthStencilStateData()
{
	depthTestEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
	depthWriteEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
	compareOp = static_cast<VkCompareOp>(std::numeric_limits<std::uint32_t>::max());
	minDepth = std::numeric_limits<float>::max();
	maxDepth = std::numeric_limits<float>::lowest();
	padding = 0;
}

PipelineColorBlendAttachment::PipelineColorBlendAttachment()
{
	blendEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
	srcColorBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
	dstColorBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
	colorBlendOp = static_cast<VkBlendOp>(std::numeric_limits<std::uint32_t>::max());
	srcAlphaBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
	dstAlphaBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
	alphaBlendOp = static_cast<VkBlendOp>(std::numeric_limits<std::uint32_t>::max());
	colorWriteMask = static_cast<VkColorComponentFlags>(std::numeric_limits<std::uint32_t>::max());
}

PushConstantData::PushConstantData()
{
	shaderStages = static_cast<VkShaderStageFlags>(0);
	offset = std::numeric_limits<std::uint32_t>::max();
	size = std::numeric_limits<std::uint32_t>::max();
	padding = 0;
}
