export module VulkanSimplifiers.SharedRenderPassData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SharedRenderPassData.CreationData;
import VulkanSimplifiers.SharedRenderPassData.InternalData;
import VulkanSimplifiers.SharedRenderPassData.Data;

import VulkanSimplifiers.Common.DataFormatFlags;
import VulkanSimplifiers.Common.ImageSampleFlags;
import VulkanSimplifiers.Common.ImageLayouts;

export class SharedRenderPassDataInternal
{
public:
	SharedRenderPassDataInternal(const SharedRenderPassDataCreationInfo& creationData);
	~SharedRenderPassDataInternal();

	IDObject<RenderPassAttachmentData> AddRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples, RenderPassAttachmentLoadOP loadOP,
		RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserve);

private:
	UnsortedList<RenderPassAttachmentData> _attachmentData;
};