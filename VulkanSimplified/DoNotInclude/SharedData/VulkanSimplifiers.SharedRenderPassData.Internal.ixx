module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedRenderPassData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SharedRenderPassData.CreationData;
import VulkanSimplifiers.SharedRenderPassData.InternalData;
import VulkanSimplifiers.SharedRenderPassData.Data;

import VulkanSimplifiers.Common.DataFormatFlags;
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

private:
	UnsortedList<RenderPassAttachmentData> _attachmentData;
	UnsortedList<RenderPassAttachmentReference> _attachmentReferenceData;
	UnsortedList<SubpassDependencyData> _subpassDependencies;

	VkPipelineStageFlags CompileStageFlags(PipelineStageFlags stageFlags);
	VkAccessFlags CompileAccessFlags(AccessFlags accessFlags);
};