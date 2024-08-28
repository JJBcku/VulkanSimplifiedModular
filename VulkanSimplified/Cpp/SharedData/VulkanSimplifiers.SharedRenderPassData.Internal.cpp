module VulkanSimplifiers.SharedRenderPassData.Internal;

SharedRenderPassDataInternal::SharedRenderPassDataInternal(const SharedRenderPassDataCreationInfo& creationData) :
	_attachmentData(creationData.sharedRenderPassAttachmentsInitialCapacity), _attachmentReferenceData(creationData.sharedRenderPassReferencesInitialCapacity)
{
}

SharedRenderPassDataInternal::~SharedRenderPassDataInternal()
{
}

IDObject<RenderPassAttachmentData> SharedRenderPassDataInternal::AddRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples,
	RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserve)
{
	RenderPassAttachmentData add;

	add.format = TranslateDataFormatToVkFormat(format);
	
	switch (samples)
	{
	case SAMPLE_64:
		add.samples = VK_SAMPLE_COUNT_64_BIT;
		break;
	case SAMPLE_32:
		add.samples = VK_SAMPLE_COUNT_32_BIT;
		break;
	case SAMPLE_16:
		add.samples = VK_SAMPLE_COUNT_16_BIT;
		break;
	case SAMPLE_8:
		add.samples = VK_SAMPLE_COUNT_8_BIT;
		break;
	case SAMPLE_4:
		add.samples = VK_SAMPLE_COUNT_4_BIT;
		break;
	case SAMPLE_2:
		add.samples = VK_SAMPLE_COUNT_2_BIT;
		break;
	case SAMPLE_1:
		add.samples = VK_SAMPLE_COUNT_1_BIT;
		break;
	default:
		throw std::runtime_error("SharedRenderPassDataInternal::AddRenderPassAttachment Error: Program was given an erroneous sample count value!");
	}

	switch (loadOP)
	{
	case RenderPassAttachmentLoadOP::IGNORE:
		add.loadOP = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		break;
	case RenderPassAttachmentLoadOP::CLEAR:
		add.loadOP = VK_ATTACHMENT_LOAD_OP_CLEAR;
		break;
	case RenderPassAttachmentLoadOP::LOAD:
		add.loadOP = VK_ATTACHMENT_LOAD_OP_LOAD;
		break;
	default:
		throw std::runtime_error("SharedRenderPassDataInternal::AddRenderPassAttachment Error: Program was given an erroneous load operation value!");
	}

	switch (storeOP)
	{
	case RenderPassAttachmentStoreOP::IGNORE:
		add.storeOP = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		break;
	case RenderPassAttachmentStoreOP::STORE:
		add.storeOP = VK_ATTACHMENT_STORE_OP_STORE;
		break;
	default:
		throw std::runtime_error("SharedRenderPassDataInternal::AddRenderPassAttachment Error: Program was given an erroneous store operation value!");
	}

	switch (initialLayout)
	{
	case ImageLayoutFlags::PRESENT:
		add.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		break;
	case ImageLayoutFlags::TRANSFER_DESTINATION:
		add.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		break;
	case ImageLayoutFlags::TRANSFER_SOURCE:
		add.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		break;
	case ImageLayoutFlags::SHADER_READ_ONLY:
		add.initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
		add.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
		add.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::COLOR_ATTACHMENT:
		add.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::GENERAL:
		add.initialLayout = VK_IMAGE_LAYOUT_GENERAL;
		break;
	case ImageLayoutFlags::UNDEFINED:
		add.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		break;
	default:
		throw std::runtime_error("SharedRenderPassDataInternal::AddRenderPassAttachment Error: Program was given an erroneous initial layout value!");
	}

	switch (finalLayout)
	{
	case ImageLayoutFlags::PRESENT:
		add.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		break;
	case ImageLayoutFlags::TRANSFER_DESTINATION:
		add.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		break;
	case ImageLayoutFlags::TRANSFER_SOURCE:
		add.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		break;
	case ImageLayoutFlags::SHADER_READ_ONLY:
		add.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
		add.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
		add.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::COLOR_ATTACHMENT:
		add.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::GENERAL:
		add.finalLayout = VK_IMAGE_LAYOUT_GENERAL;
		break;
	case ImageLayoutFlags::UNDEFINED:
		add.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		break;
	default:
		throw std::runtime_error("SharedRenderPassDataInternal::AddRenderPassAttachment Error: Program was given an erroneous final layout value!");
	}

	return _attachmentData.AddUniqueObject(std::move(add), addOnReserve);
}

IDObject<RenderPassAttachmentReference> SharedRenderPassDataInternal::AddRenderPassAttachmentReference(std::uint32_t attachmentIndex, ImageLayoutFlags subpassUsedAttachmentLayout,
	size_t addOnReserve)
{
	RenderPassAttachmentReference add;
	add.attachmentIndex = attachmentIndex;

	switch (subpassUsedAttachmentLayout)
	{
	case ImageLayoutFlags::PRESENT:
		add.attachmentLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		break;
	case ImageLayoutFlags::TRANSFER_DESTINATION:
		add.attachmentLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		break;
	case ImageLayoutFlags::TRANSFER_SOURCE:
		add.attachmentLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		break;
	case ImageLayoutFlags::SHADER_READ_ONLY:
		add.attachmentLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
		add.attachmentLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		break;
	case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
		add.attachmentLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::COLOR_ATTACHMENT:
		add.attachmentLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		break;
	case ImageLayoutFlags::GENERAL:
		add.attachmentLayout = VK_IMAGE_LAYOUT_GENERAL;
		break;
	case ImageLayoutFlags::UNDEFINED:
		add.attachmentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		break;
	default:
		throw std::runtime_error("SharedRenderPassDataInternal::AddRenderPassAttachment Error: Program was given an erroneous subpasses used attachment layout value!");
	}

	return _attachmentReferenceData.AddUniqueObject(std::move(add), addOnReserve);
}
