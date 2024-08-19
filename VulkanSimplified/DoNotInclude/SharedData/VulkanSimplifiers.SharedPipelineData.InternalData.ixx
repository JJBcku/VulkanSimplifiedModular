export module VulkanSimplifiers.SharedPipelineData.InternalData;

import std;

export struct ShaderSpecializationElement
{
	std::uint32_t ID;
	std::uint32_t offset;
	size_t size;

	ShaderSpecializationElement();
};