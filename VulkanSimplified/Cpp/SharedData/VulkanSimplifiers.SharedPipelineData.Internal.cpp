module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SharedPipelineData.Internal;

SharedPipelineDataInternal::SharedPipelineDataInternal(const SharedPipelineDataCreationInfo& initInfo) : _shaderSpecializationElements(initInfo.initialSpecializationElementsCapacity),
_shaderPipelineInfo(initInfo.initialShaderPipelineInfoCapacity), _vertexBindingInfo(initInfo.initialVertexBindingInfoCapacity),
_vertexAttributeInfo(initInfo.initialVertexAttributeInfoCapacity), _vertexPipelineInfo(initInfo.initialVertexInputPipelineInfoCapacity),
_pipelineInputAssemblyInfo(initInfo.initialPipelineInputAssemblyInfoCapacity), _pipelineRasterizationInfo(initInfo.initialPipelineRasterizationInfoCapacity),
_pipelineMultisampleInfo(initInfo.initialPipelineMultisampleInfoCapacity), _pipelineDepthStencilInfo(initInfo.initialPipelineDepthStencilInfoCapacity),
_pipelineColorBlendAttachmentInfo(initInfo.initialPipelineColorBlendAttachmentInfoCapacity), _pushContantData(initInfo.initialPushConstantDataCapacity)
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

IDObject<VertexBindingDescriptionData> SharedPipelineDataInternal::AddVertexBindingData(std::uint32_t stride, VertexBindingInputRate inputRate,
	const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserve)
{
	VertexBindingDescriptionData add;
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

	add.vertexAttributes = vertexAttributeIDs;

	return _vertexBindingInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<VertexAttributeDescriptionData> SharedPipelineDataInternal::AddVertexAttributeData(std::uint32_t offset, DataFormatSetIndependentID format, size_t addOnReserve)
{
	VertexAttributeDescriptionData add;
	add.format = TranslateDataFormatToVkFormat(format);
	add.offset = offset;

	return _vertexAttributeInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<VertexInputSharedPipelineData> SharedPipelineDataInternal::AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
	size_t addOnReserve)
{
	VertexInputSharedPipelineData add;
	add.vertexBindings = bindings;

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

	return _pipelineRasterizationInfo.AddUniqueObject(std::move(add), addOnReserve);
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
		add.minSampleShading = static_cast<float>(minSampleShading.value()) / static_cast<float>(std::numeric_limits<std::uint32_t>::max());
	}
	else
	{
		add.sampleShadingEnable = VK_FALSE;
		add.minSampleShading = 0;
	}

	return _pipelineMultisampleInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<PipelineDepthStencilStateData> SharedPipelineDataInternal::AddPipelineDepthStencilStateData(DepthUsage depthUsage, CompareOperationsType compareOp,
	float minDepth, float maxDepth, size_t addOnReserve)
{
	PipelineDepthStencilStateData add;

	switch (depthUsage)
	{
	case DepthUsage::TEST_AND_WRITE:
		add.depthTestEnable = VK_TRUE;
		add.depthWriteEnable = VK_TRUE;
		break;
	case DepthUsage::WRITE:
		add.depthTestEnable = VK_FALSE;
		add.depthWriteEnable = VK_TRUE;
		break;
	case DepthUsage::TEST:
		add.depthTestEnable = VK_TRUE;
		add.depthWriteEnable = VK_FALSE;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddPipelineDepthStencilStateData Error: Program was given an erroneous pipeline depth usage value!");
	}

	switch (compareOp)
	{
	case CompareOperationsType::COMPARE_OPERATION_NOT_EQUAL:
		add.compareOp = VK_COMPARE_OP_NOT_EQUAL;
		break;
	case CompareOperationsType::COMPARE_OPERATION_GREATER_OR_EQUAL:
		add.compareOp = VK_COMPARE_OP_GREATER_OR_EQUAL;
		break;
	case CompareOperationsType::COMPARE_OPERATION_GREATER:
		add.compareOp = VK_COMPARE_OP_GREATER;
		break;
	case CompareOperationsType::COMPARE_OPERATION_LESS_OR_EQUAL:
		add.compareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		break;
	case CompareOperationsType::COMPARE_OPERATION_LESS:
		add.compareOp = VK_COMPARE_OP_LESS;
		break;
	case CompareOperationsType::COMPARE_OPERATION_EQUAL:
		add.compareOp = VK_COMPARE_OP_EQUAL;
		break;
	case CompareOperationsType::COMPARE_OPERATION_ALWAYS:
		add.compareOp = VK_COMPARE_OP_ALWAYS;
		break;
	case CompareOperationsType::COMPARE_OPERATION_NEVER:
		add.compareOp = VK_COMPARE_OP_NEVER;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddPipelineDepthStencilStateData Error: Program was given an erroneous compare operation value!");
	}

	add.minDepth = minDepth;
	add.maxDepth = maxDepth;

	return _pipelineDepthStencilInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<PipelineColorBlendAttachment> SharedPipelineDataInternal::AddPipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
	ColorBlendingPreset blendingPreset, size_t addOnReserve)
{
	PipelineColorBlendAttachment add;

	switch (blendingPreset)
	{
	case ColorBlendingPreset::NO_BLENDING:
		add.blendEnable = VK_FALSE;
		add.srcColorBlend = VK_BLEND_FACTOR_ONE;
		add.dstColorBlend = VK_BLEND_FACTOR_ZERO;
		add.colorBlendOp = VK_BLEND_OP_ADD;
		add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
		add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
		add.alphaBlendOp = VK_BLEND_OP_ADD;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddPipelineColorBlendAttachment Error: Program was given an erroneous blending preset value!");
	}

	add.colorWriteMask = 0;

	if ((blendingComponents & COLOR_COMPONENT_R) == COLOR_COMPONENT_R)
	{
		add.colorWriteMask |= VK_COLOR_COMPONENT_R_BIT;
		blendingComponents ^= COLOR_COMPONENT_R;
	}

	if ((blendingComponents & COLOR_COMPONENT_G) == COLOR_COMPONENT_G)
	{
		add.colorWriteMask |= VK_COLOR_COMPONENT_G_BIT;
		blendingComponents ^= COLOR_COMPONENT_G;
	}

	if ((blendingComponents & COLOR_COMPONENT_B) == COLOR_COMPONENT_B)
	{
		add.colorWriteMask |= VK_COLOR_COMPONENT_B_BIT;
		blendingComponents ^= COLOR_COMPONENT_B;
	}

	if ((blendingComponents & COLOR_COMPONENT_A) == COLOR_COMPONENT_A)
	{
		add.colorWriteMask |= VK_COLOR_COMPONENT_A_BIT;
		blendingComponents ^= COLOR_COMPONENT_A;
	}

	if (blendingComponents != 0)
		throw std::runtime_error("SharedPipelineDataInternal::AddPipelineColorBlendAttachment Error: Program was given an erroneous blending components value!");

	return _pipelineColorBlendAttachmentInfo.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<PushConstantData> SharedPipelineDataInternal::AddPushConstantData(ShaderTypeFlagBit shaderType, std::uint32_t offset, std::uint32_t size, size_t addOnReserve)
{
	PushConstantData add;
	
	switch (shaderType)
	{
	case SHADER_TYPE_VERTEX:
		add.shaderStages = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case SHADER_TYPE_FRAGMENT:
		add.shaderStages = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddPushConstantData Error: Program was given an erroneous shader type value!");
	}

	add.offset = offset;
	add.size = size;

	return _pushContantData.AddUniqueObject(std::move(add), addOnReserve);
}
