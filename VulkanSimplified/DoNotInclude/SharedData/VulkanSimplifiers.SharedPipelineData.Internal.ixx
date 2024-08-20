export module VulkanSimplifiers.SharedPipelineData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SharedPipelineData.InternalData;
import VulkanSimplifiers.SharedPipelineData.CreationData;
import VulkanSimplifiers.SharedPipelineData.Data;

import VulkanSimplifiers.Common.DataFormatFlags;

export class SharedPipelineDataInternal
{
public:
	SharedPipelineDataInternal(SharedPipelineDataCreationInfo initInfo);
	~SharedPipelineDataInternal();

	IDObject<ShaderSpecializationElement> AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve);
	IDObject<ShaderSharedPipelineData> AddShaderSharedPipelineData(const std::string& entryPointName,
		const std::vector<IDObject<ShaderSpecializationElement>>& specializations, size_t addOnReserve);

	IDObject<VertexBindingDescriptionData> AddVertexBindingData(std::uint32_t binding, std::uint32_t stride, VertexBindingInputRate inputRate, size_t addOnReserve);
	IDObject<VertexAttributeDescriptionData> AddVertexAttributeData(std::uint32_t location, std::uint32_t binding, std::uint32_t offset, DataFormatSetIndependentID format,
		size_t addOnReserve);
	IDObject<VertexInputSharedPipelineData> AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
		const std::vector<IDObject<VertexAttributeDescriptionData>>& attributes, size_t addOnReserve);

	IDObject<PipelineInputAssemblyData> AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserve);
	IDObject<PipelineRasterizationData> AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise, size_t addOnReserve);

private:
	UnsortedList<ShaderSpecializationElement> _shaderSpecializationElements;
	UnsortedList<ShaderSharedPipelineData> _shaderPipelineInfo;

	UnsortedList<VertexBindingDescriptionData> _vertexBindingInfo;
	UnsortedList<VertexAttributeDescriptionData> _vertexAttributeInfo;
	UnsortedList<VertexInputSharedPipelineData> _vertexPipelineInfo;

	UnsortedList<PipelineInputAssemblyData> _pipelineInputAssemblyInfo;
	UnsortedList<PipelineRasterizationData> _pipelineRasterizationInfo;
};