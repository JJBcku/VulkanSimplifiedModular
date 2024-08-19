module VulkanSimplifiers.SharedPipelineData.Internal;

SharedPipelineDataInternal::SharedPipelineDataInternal(SharedPipelineDataCreationInfo initInfo) : _shaderSpecializationElements(initInfo.initialSpecializationElementsCapacity),
_shaderPipelineInfo(initInfo.initialShaderPipelineInfoCapacity)
{
}

SharedPipelineDataInternal::~SharedPipelineDataInternal()
{
}

IDObject<ShaderSpecializationElement> SharedPipelineDataInternal::AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve)
{
	ShaderSpecializationElement add;
	add.ID = constantID;
	add.offset = dataOffset;
	add.size = dataSize;

	return _shaderSpecializationElements.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<ShaderSharedPipelineData> SharedPipelineDataInternal::AddShaderSharedPipelineData(const std::string& entryPointName,
	const std::vector<IDObject<ShaderSpecializationElement>>& specializations, size_t addOnReserve)
{
	ShaderSharedPipelineData add;
	add.entryPointName = entryPointName;
	add.specializationElements = specializations;

	return _shaderPipelineInfo.AddUniqueObject(std::move(add), addOnReserve);
}
