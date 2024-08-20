export module VulkanSimplifiers.SharedPipelineData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SharedPipelineData.Internal;
import VulkanSimplifiers.SharedPipelineData.Data;

import VulkanSimplifiers.Common.DataFormatFlags;

export class SharedPipelineDataSimplifier
{
public:
	SharedPipelineDataSimplifier(SharedPipelineDataInternal& ref);
	~SharedPipelineDataSimplifier();

	SharedPipelineDataSimplifier& operator=(const SharedPipelineDataSimplifier&) noexcept = delete;

	IDObject<ShaderSpecializationElement> AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve = 0);
	IDObject<ShaderSharedPipelineData> AddShaderSharedPipelineData(const std::string& entryPointName,
		const std::vector<IDObject<ShaderSpecializationElement>>& specializations, size_t addOnReserve = 0);

	IDObject<VertexBindingDescriptionData> AddVertexBindingData(std::uint32_t binding, std::uint32_t stride, VertexBindingInputRate inputRate, size_t addOnReserve = 0);
	IDObject<VertexAttributeDescriptionData> AddVertexAttributeData(std::uint32_t location, std::uint32_t binding, std::uint32_t offset, DataFormatSetIndependentID format,
		size_t addOnReserve);
	IDObject<VertexInputSharedPipelineData> AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
		const std::vector<IDObject<VertexAttributeDescriptionData>>& attributes, size_t addOnReserve = 0);

	IDObject<PipelineInputAssemblyData> AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserve = 0);
	IDObject<PipelineRasterizationData> AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise, size_t addOnReserve = 0);

private:
	SharedPipelineDataInternal& _internal;
};