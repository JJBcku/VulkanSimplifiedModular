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