module VulkanSimplifiers.SharedPipelineData;

SharedPipelineDataSimplifier::SharedPipelineDataSimplifier(SharedPipelineDataInternal& ref) : _internal(ref)
{
}

SharedPipelineDataSimplifier::~SharedPipelineDataSimplifier()
{
}

IDObject<ShaderSpecializationElement> SharedPipelineDataSimplifier::AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve)
{
	return _internal.AddShaderSpecializationElement(constantID, dataOffset, dataSize, addOnReserve);
}

IDObject<ShaderSharedPipelineData> SharedPipelineDataSimplifier::AddShaderSharedPipelineData(const std::string& entryPointName,
	const std::vector<IDObject<ShaderSpecializationElement>>& specializations, size_t addOnReserve)
{
	return _internal.AddShaderSharedPipelineData(entryPointName, specializations, addOnReserve);
}
