module VulkanSimplifiers.SharedPipelineData.Internal;

SharedPipelineDataInternal::SharedPipelineDataInternal(SharedPipelineDataCreationInfo initInfo) : _shaderSpecializationElements(initInfo.initialSpecializationElementsCapacity),
_shaderPipelineInfo(initInfo.initialShaderPipelineInfoCapacity), _vertexBindingInfo(initInfo.initialVertexBindingInfoCapacity),
_vertexAttributeInfo(initInfo.initialVertexAttributeInfoCapacity), _vertexPipelineInfo(initInfo.initialVertexInputPipelineInfoCapacity)
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

IDObject<VertexBindingDescriptionData> SharedPipelineDataInternal::AddVertexBindingData(std::uint32_t binding, std::uint32_t stride, VertexBindingInputRate inputRate, size_t addOnReserve)
{
	VertexBindingDescriptionData add;
	add.binding = binding;
	add.stride = stride;

	switch (inputRate)
	{
	case VertexBindingInputRate::INSTANCE:
		add.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		break;
	case VertexBindingInputRate::VERTEX:
		add.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddVertexBindingData Error: Program was give an erroneous input rate value!");
	}

	return _vertexBindingInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<VertexAttributeDescriptionData> SharedPipelineDataInternal::AddVertexAttributeData(std::uint32_t location, std::uint32_t binding, std::uint32_t offset,
	DataFormatSetIndependentID format, size_t addOnReserve)
{
	VertexAttributeDescriptionData add;
	add.location = location;
	add.binding = binding;
	add.format = TranslateDataFormatToVkFormat(format);
	add.offset = offset;

	return _vertexAttributeInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<VertexInputSharedPipelineData> SharedPipelineDataInternal::AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
	const std::vector<IDObject<VertexAttributeDescriptionData>>& attributes, size_t addOnReserve)
{
	VertexInputSharedPipelineData add;
	add.vectorBindings = bindings;
	add.vectorAttributes = attributes;

	return _vertexPipelineInfo.AddUniqueObject(std::move(add), addOnReserve);
}
