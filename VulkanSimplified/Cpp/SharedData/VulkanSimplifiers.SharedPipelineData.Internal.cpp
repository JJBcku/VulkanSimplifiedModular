module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SharedPipelineData.Internal;

SharedPipelineDataInternal::SharedPipelineDataInternal(const SharedPipelineDataCreationInfo& initInfo) : _shaderSpecializationElements(initInfo.initialSpecializationElementsCapacity),
_shaderPipelineInfo(initInfo.initialShaderPipelineInfoCapacity), _vertexBindingInfo(initInfo.initialVertexBindingInfoCapacity),
_vertexAttributeInfo(initInfo.initialVertexAttributeInfoCapacity), _vertexPipelineInfo(initInfo.initialVertexInputPipelineInfoCapacity),
_pipelineViewportData(initInfo.initialPipelineViewportDataCapacity), _pipelineScissorData(initInfo.initialPipelineScissorDataCapacity),
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

IDObject<ShaderSharedPipelineData> SharedPipelineDataInternal::AddShaderSharedPipelineData(std::string& entryPointName, ShaderTypeFlagBit shaderType, size_t addOnReserve)
{
	ShaderSharedPipelineData add;

	switch (shaderType)
	{
	case SHADER_TYPE_VERTEX:
		add.shaderStages = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case SHADER_TYPE_FRAGMENT:
		add.shaderStages = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	default:
		throw std::runtime_error("SharedPipelineDataInternal::AddShaderSharedPipelineData Error: Program was given an erroneous shader type value!");
	}

	add.entryPointName = std::move(entryPointName);

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

IDObject<PipelineViewportData> SharedPipelineDataInternal::AddPipelineViewportData(std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height,
	float minDepth, float maxDepth, size_t addOnReserve)
{
	PipelineViewportData add;
	add.startX = static_cast<float>(startX);
	add.startY = static_cast<float>(startY);
	add.width = static_cast<float>(width);
	add.height = static_cast<float>(height);
	add.minDepth = minDepth;
	add.maxDepth = maxDepth;

	return _pipelineViewportData.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<PipelineScissorData> SharedPipelineDataInternal::AddPipelineScissorData(std::int32_t offsetX, std::int32_t offsetY, std::uint32_t width, std::uint32_t height,
	size_t addOnReserve)
{
	PipelineScissorData add;
	add.offsetX = offsetX;
	add.offsetY = offsetY;
	add.width = width;
	add.height = height;

	return _pipelineScissorData.AddUniqueObject(std::move(add), addOnReserve);
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
	case ColorBlendingPreset::ALPHA_BLENDING:
		add.blendEnable = VK_TRUE;
		add.srcColorBlend = VK_BLEND_FACTOR_SRC_ALPHA;
		add.dstColorBlend = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		add.colorBlendOp = VK_BLEND_OP_ADD;
		add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
		add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
		add.alphaBlendOp = VK_BLEND_OP_ADD;
		break;
	case ColorBlendingPreset::ADDITIVE_BLENDING:
		add.blendEnable = VK_TRUE;
		add.srcColorBlend = VK_BLEND_FACTOR_SRC_ALPHA;
		add.dstColorBlend = VK_BLEND_FACTOR_ONE;
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

std::vector<VkSpecializationMapEntry> SharedPipelineDataInternal::GetShaderSpecializationData(const std::vector<IDObject<ShaderSpecializationElement>>& specializationIDs) const
{
	std::vector<VkSpecializationMapEntry> ret;
	ret.reserve(specializationIDs.size());

	auto dataList = _shaderSpecializationElements.GetObjectList(specializationIDs);

	for (auto& data : dataList)
	{
		VkSpecializationMapEntry add{};

		add.constantID = data.ID;
		add.offset = data.offset;
		add.size = data.size;

		ret.push_back(add);
	}

	return ret;
}

ShaderSharedPipelineData SharedPipelineDataInternal::GetShaderSharedPipelineData(const IDObject<ShaderSharedPipelineData>& shaderID) const
{
	return _shaderPipelineInfo.GetObjectCopy(shaderID);
}

std::vector<VertexBindingDescriptionData> SharedPipelineDataInternal::GetVertexBindingDescriptionData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindingIDs) const
{
	return _vertexBindingInfo.GetObjectList(bindingIDs);
}

std::vector<VertexAttributeDescriptionData> SharedPipelineDataInternal::GetVertexAttributeDescriptionData(const std::vector<IDObject<VertexAttributeDescriptionData>>& attributeIDs) const
{
	return _vertexAttributeInfo.GetObjectList(attributeIDs);
}

VertexInputSharedPipelineData SharedPipelineDataInternal::GetVertexInputSharedPipelineData(IDObject<VertexInputSharedPipelineData> vertexDataIDs) const
{
	return _vertexPipelineInfo.GetConstObject(vertexDataIDs);
}

VkViewport SharedPipelineDataInternal::GetViewports(const IDObject<PipelineViewportData>& viewportID) const
{
	VkViewport ret{};

	auto& data = _pipelineViewportData.GetConstObject(viewportID);

	ret.x = data.startX;
	ret.y = data.startY;
	ret.width = data.width;
	ret.height = data.height;
	ret.minDepth = data.minDepth;
	ret.maxDepth = data.maxDepth;

	return ret;
}

VkRect2D SharedPipelineDataInternal::GetScissors(const IDObject<PipelineScissorData>& scissorID) const
{
	VkRect2D ret{};

	auto& data = _pipelineScissorData.GetConstObject(scissorID);

	ret.extent.width = data.width;
	ret.extent.height = data.height;
	ret.offset.x = data.offsetX;
	ret.offset.y = data.offsetY;

	return ret;
}

VkPipelineInputAssemblyStateCreateInfo SharedPipelineDataInternal::GetInputAssembly(IDObject<PipelineInputAssemblyData> assemblyID) const
{
	VkPipelineInputAssemblyStateCreateInfo ret{};

	ret.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

	auto& data = _pipelineInputAssemblyInfo.GetConstObject(assemblyID);

	ret.topology = data.topology;
	ret.primitiveRestartEnable = data.primitiveRestartEnable;

	return ret;
}

VkPipelineRasterizationStateCreateInfo SharedPipelineDataInternal::GetRasterizationState(IDObject<PipelineRasterizationData> rasterizationID) const
{
	VkPipelineRasterizationStateCreateInfo ret{};
	ret.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	ret.depthClampEnable = VK_FALSE;
	ret.rasterizerDiscardEnable = VK_FALSE;
	ret.lineWidth = 1.0f;

	auto& data = _pipelineRasterizationInfo.GetConstObject(rasterizationID);

	ret.polygonMode = data.polygonMode;
	ret.cullMode = data.cullMode;
	ret.frontFace = data.frontFace;
	ret.depthBiasEnable = VK_FALSE;

	return ret;
}

VkPipelineMultisampleStateCreateInfo SharedPipelineDataInternal::GetMultisamplingState(IDObject<PipelineMultisampleData> multisamplingID) const
{
	VkPipelineMultisampleStateCreateInfo ret{};
	ret.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

	auto& data = _pipelineMultisampleInfo.GetConstObject(multisamplingID);

	ret.rasterizationSamples = data.sampleCount;
	ret.sampleShadingEnable = data.sampleShadingEnable;
	ret.minSampleShading = data.minSampleShading;

	return ret;
}

VkPipelineDepthStencilStateCreateInfo SharedPipelineDataInternal::GetDepthStencilState(IDObject<PipelineDepthStencilStateData> depthStencilID) const
{
	VkPipelineDepthStencilStateCreateInfo ret;
	ret.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

	auto& data = _pipelineDepthStencilInfo.GetConstObject(depthStencilID);

	ret.depthTestEnable = data.depthTestEnable;
	ret.depthWriteEnable = data.depthWriteEnable;
	ret.depthCompareOp = data.compareOp;
	ret.depthBoundsTestEnable = VK_FALSE;
	ret.stencilTestEnable = VK_FALSE;
	ret.minDepthBounds = data.minDepth;
	ret.maxDepthBounds = data.maxDepth;

	return ret;
}

std::vector<VkPipelineColorBlendAttachmentState> SharedPipelineDataInternal::GetColorBlendAttachments(const std::vector<IDObject<PipelineColorBlendAttachment>>& attachmentIDs) const
{
	std::vector<VkPipelineColorBlendAttachmentState> ret;
	ret.reserve(attachmentIDs.size());

	auto dataList = _pipelineColorBlendAttachmentInfo.GetObjectList(attachmentIDs);

	for (auto& data : dataList)
	{
		VkPipelineColorBlendAttachmentState add{};
		add.blendEnable = data.blendEnable;
		add.srcColorBlendFactor = data.srcColorBlend;
		add.dstColorBlendFactor = data.dstColorBlend;
		add.colorBlendOp = data.colorBlendOp;
		add.srcAlphaBlendFactor = data.srcAlphaBlend;
		add.dstAlphaBlendFactor = data.dstAlphaBlend;
		add.alphaBlendOp = data.alphaBlendOp;
		add.colorWriteMask = data.colorWriteMask;

		ret.push_back(add);
	}

	return ret;
}

std::vector<VkPushConstantRange> SharedPipelineDataInternal::GetPushConstantData(std::vector<IDObject<PushConstantData>> pushConstantIDs) const
{
	std::vector<VkPushConstantRange> ret;

	auto pushDataList = _pushContantData.GetObjectList(pushConstantIDs);

	ret.reserve(pushDataList.size());

	for (auto& pushData : pushDataList)
	{
		VkPushConstantRange add{};
		add.stageFlags = pushData.shaderStages;
		add.offset = pushData.offset;
		add.size = pushData.size;

		ret.push_back(add);
	}

	return ret;
}
