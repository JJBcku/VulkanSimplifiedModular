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
	IDObject<ShaderSharedPipelineData> AddShaderSharedPipelineData(std::string& entryPointName, ShaderTypeFlagBit shaderType, size_t addOnReserve);

	IDObject<VertexBindingDescriptionData> AddVertexBindingData(std::uint32_t stride, VertexBindingInputRate inputRate,
		const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserve);
	IDObject<VertexAttributeDescriptionData> AddVertexAttributeData(std::uint32_t offset, DataFormatSetIndependentID format, size_t addOnReserve);
	IDObject<VertexInputSharedPipelineData> AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings, size_t addOnReserve);

	IDObject<PipelineViewportData> AddPipelineViewportData(std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height, float minDepth, float maxDepth,
		size_t addOnReserve);
	IDObject<PipelineScissorData> AddPipelineScissorData(std::int32_t offsetX, std::int32_t offsetY, std::uint32_t width, std::uint32_t height, size_t addOnReserve);

	IDObject<PipelineInputAssemblyData> AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserve);
	IDObject<PipelineRasterizationData> AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise, size_t addOnReserve);
	IDObject<PipelineMultisampleData> AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting, std::optional<std::uint32_t> minSampleShading, size_t addOnReserve);
	IDObject<PipelineDepthStencilStateData> AddPipelineDepthStencilStateData(DepthUsage depthUsage, CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserve);
	IDObject<PipelineColorBlendAttachment> AddPipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents, ColorBlendingPreset blendingPreset, size_t addOnReserve);

	IDObject<PushConstantData> AddPushConstantData(ShaderTypeFlagBit shaderType, std::uint32_t offset, std::uint32_t size, size_t addOnReserve);

	std::vector<VkSpecializationMapEntry> GetShaderSpecializationData(const std::vector<IDObject<ShaderSpecializationElement>>& specializationIDs) const;
	ShaderSharedPipelineData GetShaderSharedPipelineData(const IDObject<ShaderSharedPipelineData>& shaderID) const;

	std::vector<VertexBindingDescriptionData> GetVertexBindingDescriptionData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindingIDs) const;
	std::vector<VertexAttributeDescriptionData> GetVertexAttributeDescriptionData(const std::vector<IDObject<VertexAttributeDescriptionData>>& attributeIDs) const;
	VertexInputSharedPipelineData GetVertexInputSharedPipelineData(IDObject<VertexInputSharedPipelineData> vertexDataIDs) const;

	VkViewport GetViewports(const IDObject<PipelineViewportData>& viewportID) const;
	VkRect2D GetScissors(const IDObject<PipelineScissorData>& scissorID) const;

	VkPipelineInputAssemblyStateCreateInfo GetInputAssembly(IDObject<PipelineInputAssemblyData> assemblyID) const;
	VkPipelineRasterizationStateCreateInfo GetRasterizationState(IDObject<PipelineRasterizationData> rasterizationID) const;
	VkPipelineMultisampleStateCreateInfo GetMultisamplingState(IDObject<PipelineMultisampleData> multisamplingID) const;
	VkPipelineDepthStencilStateCreateInfo GetDepthStencilState(IDObject<PipelineDepthStencilStateData> depthStencilID) const;
	std::vector<VkPipelineColorBlendAttachmentState> GetColorBlendAttachments(const std::vector<IDObject<PipelineColorBlendAttachment>>& attachmentIDs) const;

	std::vector<VkPushConstantRange> GetPushConstantData(std::vector<IDObject<PushConstantData>> pushConstantIDs) const;

private:
	UnsortedList<ShaderSpecializationElement> _shaderSpecializationElements;
	UnsortedList<ShaderSharedPipelineData> _shaderPipelineInfo;

	UnsortedList<VertexBindingDescriptionData> _vertexBindingInfo;
	UnsortedList<VertexAttributeDescriptionData> _vertexAttributeInfo;
	UnsortedList<VertexInputSharedPipelineData> _vertexPipelineInfo;

	UnsortedList<PipelineViewportData> _pipelineViewportData;
	UnsortedList<PipelineScissorData> _pipelineScissorData;

	UnsortedList<PipelineInputAssemblyData> _pipelineInputAssemblyInfo;
	UnsortedList<PipelineRasterizationData> _pipelineRasterizationInfo;
	UnsortedList<PipelineMultisampleData> _pipelineMultisampleInfo;
	UnsortedList<PipelineDepthStencilStateData> _pipelineDepthStencilInfo;
	UnsortedList<PipelineColorBlendAttachment> _pipelineColorBlendAttachmentInfo;

	UnsortedList<PushConstantData> _pushContantData;
};