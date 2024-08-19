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