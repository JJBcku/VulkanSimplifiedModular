module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SharedPipelineData.Internal;

SharedPipelineDataInternal::SharedPipelineDataInternal(SharedPipelineDataCreationInfo initInfo) : _shaderSpecializationElements(initInfo.initialSpecializationElementsCapacity),
_shaderPipelineInfo(initInfo.initialShaderPipelineInfoCapacity), _vertexBindingInfo(initInfo.initialVertexBindingInfoCapacity),
_vertexAttributeInfo(initInfo.initialVertexAttributeInfoCapacity), _vertexPipelineInfo(initInfo.initialVertexInputPipelineInfoCapacity),
_pipelineInputAssemblyInfo(initInfo.initialPipelineInputAssemblyInfoCapacity), _pipelineRasterizationInfo(initInfo.initialPipelineRasterizationInfoCapacity),
_pipelineMultisampleInfo(initInfo.initialPipelineMultisampleInfoCapacity)
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

IDObject<PipelineInputAssemblyData> SharedPipelineDataInternal::AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserve)
{
	PipelineInputAssemblyData add;
	
	switch (topology)
	{
	case PipelinePrimitiveTopology::PATCH_LIST:
		add.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
		break;
	case PipelinePrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
		add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
		break;
	case PipelinePrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
		add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
		break;
	case PipelinePrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
		add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
		break;
	case PipelinePrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
		add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
		break;
	case PipelinePrimitiveTopology::TRIANGLE_FAN:
		add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
		break;
	case PipelinePrimitiveTopology::TRIANGLE_STRIP:
		add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		break;
	case PipelinePrimitiveTopology::TRIANGLE_LIST:
		add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		break;
	case PipelinePrimitiveTopology::LINE_STRIP:
		add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
		break;
	case PipelinePrimitiveTopology::LINE_LIST:
		add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		break;
	case PipelinePrimitiveTopology::POINT_LIST:
		add.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddPipelineInputAssemblyData Error: Program was given an erroneous pipeline primitive topology value!");
	}

	if (primitiveRestartEnable)
		add.primitiveRestartEnable = VK_TRUE;
	else
		add.primitiveRestartEnable = VK_FALSE;

	return _pipelineInputAssemblyInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<PipelineRasterizationData> SharedPipelineDataInternal::AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise, size_t addOnReserve)
{
	PipelineRasterizationData add;
	
	switch (polygonMode)
	{
	case PipelinePolygonMode::POINT:
		add.polygonMode = VK_POLYGON_MODE_POINT;
		break;
	case PipelinePolygonMode::LINE:
		add.polygonMode = VK_POLYGON_MODE_LINE;
		break;
	case PipelinePolygonMode::FILL:
		add.polygonMode = VK_POLYGON_MODE_FILL;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddPipelineRasterizationData Error: Program was given an erroneous pipeline polygon mode value!");
	}

	if (cullPolygonBacks)
		add.cullMode = VK_CULL_MODE_BACK_BIT;
	else
		add.cullMode = VK_CULL_MODE_NONE;

	if (frontClockwise)
		add.frontFace = VK_FRONT_FACE_CLOCKWISE;
	else
		add.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

	return _pipelineRasterizationInfo.AddUniqueObject(add, addOnReserve);
}

IDObject<PipelineMultisampleData> SharedPipelineDataInternal::AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting, std::optional<std::uint32_t> minSampleShading,
	size_t addOnReserve)
{
	PipelineMultisampleData add;

	switch (samplingSetting)
	{
	case SAMPLE_64:
		add.sampleCount = VK_SAMPLE_COUNT_64_BIT;
		break;
	case SAMPLE_32:
		add.sampleCount = VK_SAMPLE_COUNT_32_BIT;
		break;
	case SAMPLE_16:
		add.sampleCount = VK_SAMPLE_COUNT_16_BIT;
		break;
	case SAMPLE_8:
		add.sampleCount = VK_SAMPLE_COUNT_8_BIT;
		break;
	case SAMPLE_4:
		add.sampleCount = VK_SAMPLE_COUNT_4_BIT;
		break;
	case SAMPLE_2:
		add.sampleCount = VK_SAMPLE_COUNT_2_BIT;
		break;
	case SAMPLE_1:
		add.sampleCount = VK_SAMPLE_COUNT_1_BIT;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddPipelineMultisampleData Error: Program was given an erroneous pipeline sampling value!");
	}

	if (minSampleShading.has_value())
	{
		add.sampleShadingEnable = VK_TRUE;
		add.minSampleShading = minSampleShading.value();
	}
	else
	{
		add.sampleShadingEnable = VK_FALSE;
		add.minSampleShading = 0;
	}

	return _pipelineMultisampleInfo.AddUniqueObject(add, addOnReserve);
}
