module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedRenderPassData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SharedRenderPassData.CreationData;
import VulkanSimplifiers.SharedRenderPassData.InternalData;
import VulkanSimplifiers.SharedRenderPassData.Data;

import VulkanSimplifiers.Common.DataFormatFlags.Internal;
import VulkanSimplifiers.Common.ImageSampleFlags;
import VulkanSimplifiers.Common.ImageLayouts;
import VulkanSimplifiers.Common.PipelineStageFlags;
import VulkanSimplifiers.Common.AccessFlags;

export class SharedRenderPassDataInternal
{
public:
	SharedRenderPassDataInternal(const SharedRenderPassDataCreationInfo& creationData);
	~SharedRenderPassDataInternal();

	IDObject<RenderPassAttachmentData> AddRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples, RenderPassAttachmentLoadOP loadOP,
		RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserve);

	IDObject<RenderPassAttachmentReference> AddRenderPassAttachmentReference(std::uint32_t attachmentIndex, ImageLayoutFlags subpassUsedAttachmentLayout, size_t addOnReserve);

	IDObject<SubpassDependencyData> AddSubpassDependency(std::uint32_t srcSubpass, std::uint32_t dstSubpass, PipelineStageFlags srcStageFlags, PipelineStageFlags dstStageFlags,
		AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserve);

	std::vector<VkAttachmentDescription> GetRenderPassAttachmentDescriptors(const std::vector<IDObject<RenderPassAttachmentData>> attachmentIDs) const;

	std::vector<VkAttachmentReference> GetRenderPassAttachmentReferences(const std::vector<std::optional<IDObject<RenderPassAttachmentReference>>>& referenceIDs) const;
	VkAttachmentReference GetRenderPassAttachmentReference(const std::optional<IDObject<RenderPassAttachmentReference>>& referenceID) const;

	std::vector<VkSubpassDependency> GetSubpassDependencies(const std::vector<IDObject<SubpassDependencyData>>& dependencyIDs) const;

	IDObject<RenderPassDoubleColorClearValues> AddDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserve);
	IDObject<RenderPassInt64ColorClearValues> AddInt64ColorClearValue(std::int64_t r, std::int64_t g, std::int64_t b, std::int64_t a, size_t addOnReserve);
	IDObject<RenderPassUInt64ColorClearValues> AddUInt64ColorClearValue(std::uint64_t r, std::uint64_t g, std::uint64_t b, std::uint64_t a, size_t addOnReserve);

	IDObject<RenderPassFloatColorClearValues> AddFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserve);
	IDObject<RenderPassIntColorClearValues> AddIntColorClearValue(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a, size_t addOnReserve);
	IDObject<RenderPassUIntColorClearValues> AddUIntColorClearValue(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a, size_t addOnReserve);

	IDObject<RenderPassDepthStencilClearValues> AddDepthStencilClearValue(float depth, std::uint32_t stencil, size_t addOnReserve);

	std::pair<VkClearValue, std::optional<VkClearValue>> GetClearValue(RenderPassClearValuesID valueID) const;

private:
	UnsortedList<RenderPassAttachmentData> _attachmentData;
	UnsortedList<RenderPassAttachmentReference> _attachmentReferenceData;
	UnsortedList<SubpassDependencyData> _subpassDependencies;

	UnsortedList<RenderPassDoubleColorClearValues> _doubleClearValues;
	UnsortedList<RenderPassInt64ColorClearValues> _int64ClearValues;
	UnsortedList<RenderPassUInt64ColorClearValues> _uint64ClearValues;

	UnsortedList<RenderPassFloatColorClearValues> _floatClearValues;
	UnsortedList<RenderPassIntColorClearValues> _intClearValues;
	UnsortedList<RenderPassUIntColorClearValues> _uintClearValues;

	UnsortedList<RenderPassDepthStencilClearValues> _depthClearValues;

	std::pair<VkClearValue, VkClearValue> GetDoubleColorClearValue(IDObject<RenderPassDoubleColorClearValues> valueID) const;
	std::pair<VkClearValue, VkClearValue> GetInt64ColorClearValue(IDObject<RenderPassInt64ColorClearValues> valueID) const;
	std::pair<VkClearValue, VkClearValue> GetUInt64ColorClearValue(IDObject<RenderPassUInt64ColorClearValues> valueID) const;

	VkClearValue GetFloatColorClearValue(IDObject<RenderPassFloatColorClearValues> valueID) const;
	VkClearValue GetIntColorClearValue(IDObject<RenderPassIntColorClearValues> valueID) const;
	VkClearValue GetUIntColorClearValue(IDObject<RenderPassUIntColorClearValues> valueID) const;

	VkClearValue GetDepthStencilClearValue(IDObject<RenderPassDepthStencilClearValues> valueID) const;

	VkPipelineStageFlags CompileStageFlags(PipelineStageFlags stageFlags);
	VkAccessFlags CompileAccessFlags(AccessFlags accessFlags);
};