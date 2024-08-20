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
	binding = std::numeric_limits<std::uint32_t>::max();
	stride = std::numeric_limits<std::uint32_t>::max();
	inputRate = static_cast<VkVertexInputRate>(std::numeric_limits<std::uint32_t>::max());
	padding = 0;
}

VertexAttributeDescriptionData::VertexAttributeDescriptionData()
{
	location = std::numeric_limits<std::uint32_t>::max();
	binding = std::numeric_limits<std::uint32_t>::max();
	format = VK_FORMAT_UNDEFINED;
	offset = std::numeric_limits<std::uint32_t>::max();
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
