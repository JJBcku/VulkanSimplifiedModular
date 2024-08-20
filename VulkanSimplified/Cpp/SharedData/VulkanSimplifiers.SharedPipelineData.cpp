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

IDObject<VertexBindingDescriptionData> SharedPipelineDataSimplifier::AddVertexBindingData(std::uint32_t binding, std::uint32_t stride, VertexBindingInputRate inputRate,
	size_t addOnReserve)
{
	return _internal.AddVertexBindingData(binding, stride, inputRate, addOnReserve);
}

IDObject<VertexAttributeDescriptionData> SharedPipelineDataSimplifier::AddVertexAttributeData(std::uint32_t location, std::uint32_t binding, std::uint32_t offset,
	DataFormatSetIndependentID format, size_t addOnReserve)
{
	return _internal.AddVertexAttributeData(location, binding, offset, format, addOnReserve);
}

IDObject<VertexInputSharedPipelineData> SharedPipelineDataSimplifier::AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
	const std::vector<IDObject<VertexAttributeDescriptionData>>& attributes, size_t addOnReserve)
{
	return _internal.AddVertexInputSharedPipelineData(bindings, attributes, addOnReserve);
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

IDObject<PipelineDepthStencilStateData> SharedPipelineDataSimplifier::AddPipelineDepthStencilStateData(DepthUsage depthUsage, CompareOperationType compareOp,
	float minDepth, float maxDepth, size_t addOnReserve)
{
	return _internal.AddPipelineDepthStencilStateData(depthUsage, compareOp, minDepth, maxDepth, addOnReserve);
}
