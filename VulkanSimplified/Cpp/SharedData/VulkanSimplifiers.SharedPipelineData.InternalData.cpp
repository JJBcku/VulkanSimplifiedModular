module VulkanSimplifiers.SharedPipelineData.InternalData;

ShaderSpecializationElement::ShaderSpecializationElement()
{
	ID = std::numeric_limits<std::uint32_t>::max();
	offset = std::numeric_limits<std::uint32_t>::max();
	size  = std::numeric_limits<size_t>::max();
}