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
	std::string entryPointName;
	std::vector<IDObject<ShaderSpecializationElement>> specializationElements;

	ShaderSharedPipelineData() = default;

	bool operator==(const ShaderSharedPipelineData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const ShaderSharedPipelineData& rhs) const noexcept = default;
};

export struct VertexBindingDescriptionData
{
	std::uint32_t binding;
	std::uint32_t stride;
	VkVertexInputRate inputRate;
	std::uint32_t padding;

	VertexBindingDescriptionData();

	bool operator==(const VertexBindingDescriptionData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const VertexBindingDescriptionData & rhs) const noexcept = default;
};

export struct VertexAttributeDescriptionData
{
	std::uint32_t location;
	std::uint32_t binding;
	VkFormat format;
	std::uint32_t offset;

	VertexAttributeDescriptionData();

	bool operator==(const VertexAttributeDescriptionData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const VertexAttributeDescriptionData& rhs) const noexcept = default;
};

export struct VertexInputSharedPipelineData
{
	std::vector<IDObject<VertexBindingDescriptionData>> vectorBindings;
	std::vector<IDObject<VertexAttributeDescriptionData>> vectorAttributes;

	VertexInputSharedPipelineData() = default;

	bool operator==(const VertexInputSharedPipelineData& rhs) const noexcept = default;
	std::strong_ordering operator<=>(const VertexInputSharedPipelineData& rhs) const noexcept = default;
};
