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

IDObject<VertexBindingDescriptionData> SharedPipelineDataSimplifier::AddVertexBindingData(std::uint32_t stride, VertexBindingInputRate inputRate,
	const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserve)
{
	return _internal.AddVertexBindingData(stride, inputRate, vertexAttributeIDs, addOnReserve);
}

IDObject<VertexAttributeDescriptionData> SharedPipelineDataSimplifier::AddVertexAttributeData(std::uint32_t offset, DataFormatSetIndependentID format, size_t addOnReserve)
{
	return _internal.AddVertexAttributeData(offset, format, addOnReserve);
}

IDObject<VertexInputSharedPipelineData> SharedPipelineDataSimplifier::AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
	size_t addOnReserve)
{
	return _internal.AddVertexInputSharedPipelineData(bindings, addOnReserve);
}

IDObject<PipelineViewportData> SharedPipelineDataSimplifier::AddPipelineViewportData(std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height, float minDepth, float maxDepth, size_t addOnReserve)
{
	return _internal.AddPipelineViewportData(startX, startY, width, height, minDepth, maxDepth, addOnReserve);
}

IDObject<PipelineScissorData> SharedPipelineDataSimplifier::AddPipelineScissorData(std::int32_t offsetX, std::int32_t offsetY, std::uint32_t width, std::uint32_t height,
	size_t addOnReserve)
{
	return _internal.AddPipelineScissorData(offsetX, offsetY, width, height, addOnReserve);
}

IDObject<PipelineInputAssemblyData> SharedPipelineDataSimplifier::AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserve)
{
	return _internal.AddPipelineInputAssemblyData(topology, primitiveRestartEnable, addOnReserve);
}

IDObject<PipelineRasterizationData> SharedPipelineDataSimplifier::AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise,
	size_t addOnReserve)
{
	return _internal.AddPipelineRasterizationData(polygonMode, cullPolygonBacks, frontClockwise, addOnReserve);
}

IDObject<PipelineMultisampleData> SharedPipelineDataSimplifier::AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting, std::optional<std::uint32_t> minSampleShading,
	size_t addOnReserve)
{
	return _internal.AddPipelineMultisampleData(samplingSetting, minSampleShading, addOnReserve);
}

IDObject<PipelineDepthStencilStateData> SharedPipelineDataSimplifier::AddPipelineDepthStencilStateData(DepthUsage depthUsage, CompareOperationsType compareOp,
	float minDepth, float maxDepth, size_t addOnReserve)
{
	return _internal.AddPipelineDepthStencilStateData(depthUsage, compareOp, minDepth, maxDepth, addOnReserve);
}

IDObject<PipelineColorBlendAttachment> SharedPipelineDataSimplifier::AddPipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
	ColorBlendingPreset blendingPreset, size_t addOnReserve)
{
	return _internal.AddPipelineColorBlendAttachment(blendingComponents, blendingPreset, addOnReserve);
}

IDObject<PushConstantData> SharedPipelineDataSimplifier::AddPushConstantData(ShaderTypeFlagBit shaderType, std::uint32_t offset, std::uint32_t size, size_t addOnReserve)
{
	return _internal.AddPushConstantData(shaderType, offset, size, addOnReserve);
}
