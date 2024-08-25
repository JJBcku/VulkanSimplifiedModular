module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedPipelineData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SharedPipelineData.InternalData;
import VulkanSimplifiers.SharedPipelineData.CreationData;
import VulkanSimplifiers.SharedPipelineData.Data;

import VulkanSimplifiers.Common.DataFormatFlags;
import VulkanSimplifiers.Common.ImageSampleFlags;
import VulkanSimplifiers.Common.CompareOperationsType;
import VulkanSimplifiers.Common.ShaderTypeFlags;

export class SharedPipelineDataInternal
{
public:
	SharedPipelineDataInternal(const SharedPipelineDataCreationInfo& initInfo);
	~SharedPipelineDataInternal();

	IDObject<ShaderSpecializationElement> AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve);
	IDObject<ShaderSharedPipelineData> AddShaderSharedPipelineData(const std::string& entryPointName,
		const std::vector<IDObject<ShaderSpecializationElement>>& specializations, size_t addOnReserve);

	IDObject<VertexBindingDescriptionData> AddVertexBindingData(std::uint32_t stride, VertexBindingInputRate inputRate,
		const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserve);
	IDObject<VertexAttributeDescriptionData> AddVertexAttributeData(std::uint32_t offset, DataFormatSetIndependentID format, size_t addOnReserve);
	IDObject<VertexInputSharedPipelineData> AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings, size_t addOnReserve);

	IDObject<PipelineInputAssemblyData> AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserve);
	IDObject<PipelineRasterizationData> AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise, size_t addOnReserve);
	IDObject<PipelineMultisampleData> AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting, std::optional<std::uint32_t> minSampleShading, size_t addOnReserve);
	IDObject<PipelineDepthStencilStateData> AddPipelineDepthStencilStateData(DepthUsage depthUsage, CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserve);
	IDObject<PipelineColorBlendAttachment> AddPipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents, ColorBlendingPreset blendingPreset, size_t addOnReserve);

	IDObject<PushConstantData> AddPushConstantData(ShaderTypeFlagBit shaderType, std::uint32_t offset, std::uint32_t size, size_t addOnReserve);

	std::vector<VkPushConstantRange> GetPushConstantData(std::vector<IDObject<PushConstantData>> pushConstantIDs) const;

private:
	UnsortedList<ShaderSpecializationElement> _shaderSpecializationElements;
	UnsortedList<ShaderSharedPipelineData> _shaderPipelineInfo;

	UnsortedList<VertexBindingDescriptionData> _vertexBindingInfo;
	UnsortedList<VertexAttributeDescriptionData> _vertexAttributeInfo;
	UnsortedList<VertexInputSharedPipelineData> _vertexPipelineInfo;

	UnsortedList<PipelineInputAssemblyData> _pipelineInputAssemblyInfo;
	UnsortedList<PipelineRasterizationData> _pipelineRasterizationInfo;
	UnsortedList<PipelineMultisampleData> _pipelineMultisampleInfo;
	UnsortedList<PipelineDepthStencilStateData> _pipelineDepthStencilInfo;
	UnsortedList<PipelineColorBlendAttachment> _pipelineColorBlendAttachmentInfo;

	UnsortedList<PushConstantData> _pushContantData;
};