export module VulkanSimplifiers.SharedPipelineData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SharedPipelineData.Internal;
import VulkanSimplifiers.SharedPipelineData.Data;

import VulkanSimplifiers.Common.DataFormatFlags;
import VulkanSimplifiers.Common.ImageSampleFlags;
import VulkanSimplifiers.Common.CompareOperationsType;
import VulkanSimplifiers.Common.ShaderTypeFlags;

export class SharedPipelineDataSimplifier
{
public:
	SharedPipelineDataSimplifier(SharedPipelineDataInternal& ref);
	~SharedPipelineDataSimplifier();

	SharedPipelineDataSimplifier& operator=(const SharedPipelineDataSimplifier&) noexcept = delete;

	IDObject<ShaderSpecializationElement> AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve = 0);
	IDObject<ShaderSharedPipelineData> AddShaderSharedPipelineData(std::string entryPointName, ShaderTypeFlagBit shaderType, size_t addOnReserve = 0);

	IDObject<VertexBindingDescriptionData> AddVertexBindingData(std::uint32_t stride, VertexBindingInputRate inputRate,
		const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserve = 0);
	IDObject<VertexAttributeDescriptionData> AddVertexAttributeData(std::uint32_t offset, DataFormatSetIndependentID format, size_t addOnReserve = 0);
	IDObject<VertexInputSharedPipelineData> AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings, size_t addOnReserve = 0);

	IDObject<PipelineViewportData> AddPipelineViewportData(std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height, float minDepth, float maxDepth,
		size_t addOnReserve = 0);
	IDObject<PipelineScissorData> AddPipelineScissorData(std::int32_t offsetX, std::int32_t offsetY, std::uint32_t width, std::uint32_t height, size_t addOnReserve = 0);

	IDObject<PipelineInputAssemblyData> AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserve = 0);
	IDObject<PipelineRasterizationData> AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise, size_t addOnReserve = 0);
	IDObject<PipelineMultisampleData> AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting, std::optional<std::uint32_t> minSampleShading, size_t addOnReserve = 0);
	IDObject<PipelineDepthStencilStateData> AddPipelineDepthStencilStateData(DepthUsage depthUsage, CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserve = 0);
	IDObject<PipelineColorBlendAttachment> AddPipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents, ColorBlendingPreset blendingPreset, size_t addOnReserve = 0);

	IDObject<PushConstantData> AddPushConstantData(ShaderTypeFlagBit shaderType, std::uint32_t offset, std::uint32_t size, size_t addOnReserve = 0);

private:
	SharedPipelineDataInternal& _internal;
};