module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SharedRenderPassData.Internal;

SharedRenderPassDataInternal::SharedRenderPassDataInternal(const SharedRenderPassDataCreationInfo& creationData) :
	_attachmentData(creationData.sharedRenderPassAttachmentsInitialCapacity), _attachmentReferenceData(creationData.sharedRenderPassReferencesInitialCapacity),
	_subpassDependencies(creationData.sharedSubpassDependenciesInitialCapacity)
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

IDObject<SubpassDependencyData> SharedRenderPassDataInternal::AddSubpassDependency(std::uint32_t srcSubpass, std::uint32_t dstSubpass, PipelineStageFlags srcStageFlags,
	PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserve)
{
	SubpassDependencyData add;

	add.srcSubpass = srcSubpass;
	add.dstSubpass = dstSubpass;

	add.srcStageFlags = CompileStageFlags(srcStageFlags);
	add.dstStageFlags = CompileStageFlags(dstStageFlags);

	add.srcAccessFlags = CompileAccessFlags(srcAccessFlags);
	add.dstAccessFlags = CompileAccessFlags(dstAccessFlags);

	return _subpassDependencies.AddUniqueObject(std::move(add), addOnReserve);
}

VkPipelineStageFlags SharedRenderPassDataInternal::CompileStageFlags(PipelineStageFlags stageFlags)
{
	VkPipelineStageFlags ret = 0;

	if ((stageFlags & PIPELINE_STAGE_TOP_OF_PIPE) == PIPELINE_STAGE_TOP_OF_PIPE)
		ret |= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

	if ((stageFlags & PIPELINE_STAGE_DRAW_INDIRECT) == PIPELINE_STAGE_DRAW_INDIRECT)
		ret |= VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;

	if ((stageFlags & PIPELINE_STAGE_VERTEX_INPUT) == PIPELINE_STAGE_VERTEX_INPUT)
		ret |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;

	if ((stageFlags & PIPELINE_STAGE_VERTEX_SHADER) == PIPELINE_STAGE_VERTEX_SHADER)
		ret |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;

	if ((stageFlags & PIPELINE_STAGE_TESSELATION_CONTROL_SHADER) == PIPELINE_STAGE_TESSELATION_CONTROL_SHADER)
		ret |= VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT;

	if ((stageFlags & PIPELINE_STAGE_TESSELATION_EVALUATION_SHADER) == PIPELINE_STAGE_TESSELATION_EVALUATION_SHADER)
		ret |= VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT;

	if ((stageFlags & PIPELINE_STAGE_GEOMETRY_SHADER) == PIPELINE_STAGE_GEOMETRY_SHADER)
		ret |= VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT;

	if ((stageFlags & PIPELINE_STAGE_FRAGMENT_SHADER) == PIPELINE_STAGE_FRAGMENT_SHADER)
		ret |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;

	if ((stageFlags & PIPELINE_STAGE_EARLY_FRAGMENT_TEST) == PIPELINE_STAGE_EARLY_FRAGMENT_TEST)
		ret |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

	if ((stageFlags & PIPELINE_STAGE_LATE_FRAGMENT_TEST) == PIPELINE_STAGE_LATE_FRAGMENT_TEST)
		ret |= VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;

	if ((stageFlags & PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT) == PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT)
		ret |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	if ((stageFlags & PIPELINE_STAGE_COMPUTE_SHADER) == PIPELINE_STAGE_COMPUTE_SHADER)
		ret |= VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;

	if ((stageFlags & PIPELINE_STAGE_TRANSFER) == PIPELINE_STAGE_TRANSFER)
		ret |= VK_PIPELINE_STAGE_TRANSFER_BIT;

	if ((stageFlags & PIPELINE_STAGE_BOTTOM_OF_PIPE) == PIPELINE_STAGE_BOTTOM_OF_PIPE)
		ret |= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

	if ((stageFlags & PIPELINE_STAGE_HOST) == PIPELINE_STAGE_HOST)
		ret |= VK_PIPELINE_STAGE_HOST_BIT;

	if ((stageFlags & PIPELINE_STAGE_ALL_GRAPHICS) == PIPELINE_STAGE_ALL_GRAPHICS)
		ret |= VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;

	if ((stageFlags & PIPELINE_STAGE_ALL_COMMANDS) == PIPELINE_STAGE_ALL_COMMANDS)
		ret |= VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

	return ret;
}

VkAccessFlags SharedRenderPassDataInternal::CompileAccessFlags(AccessFlags accessFlags)
{
	VkAccessFlags ret = 0;

	if ((accessFlags & ACCESS_INDIRECT_COMMAND) == ACCESS_INDIRECT_COMMAND)
		ret |= VK_ACCESS_INDIRECT_COMMAND_READ_BIT;

	if ((accessFlags & ACCESS_INDEX_READ) == ACCESS_INDEX_READ)
		ret |= VK_ACCESS_INDEX_READ_BIT;

	if ((accessFlags & ACCESS_VERTEX_ATTRIBUTE_READ) == ACCESS_VERTEX_ATTRIBUTE_READ)
		ret |= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;

	if ((accessFlags & ACCESS_UNIFORM_READ) == ACCESS_UNIFORM_READ)
		ret |= VK_ACCESS_UNIFORM_READ_BIT;

	if ((accessFlags & ACCESS_INPUT_ATTACHMENT_READ) == ACCESS_INPUT_ATTACHMENT_READ)
		ret |= VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;

	if ((accessFlags & ACCESS_SHADER_READ) == ACCESS_SHADER_READ)
		ret |= VK_ACCESS_SHADER_READ_BIT;

	if ((accessFlags & ACCESS_SHADER_WRITE) == ACCESS_SHADER_WRITE)
		ret |= VK_ACCESS_SHADER_WRITE_BIT;

	if ((accessFlags & ACCESS_COLOR_READ) == ACCESS_COLOR_READ)
		ret |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

	if ((accessFlags & ACCESS_COLOR_WRITE) == ACCESS_COLOR_WRITE)
		ret |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	if ((accessFlags & ACCESS_DEPTH_STENCIL_READ) == ACCESS_DEPTH_STENCIL_READ)
		ret |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

	if ((accessFlags & ACCESS_DEPTH_STENCIL_WRITE) == ACCESS_DEPTH_STENCIL_WRITE)
		ret |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	if ((accessFlags & ACCESS_TRANSFER_READ) == ACCESS_TRANSFER_READ)
		ret |= VK_ACCESS_TRANSFER_READ_BIT;

	if ((accessFlags & ACCESS_TRANSFER_WRITE) == ACCESS_TRANSFER_WRITE)
		ret |= VK_ACCESS_TRANSFER_WRITE_BIT;

	if ((accessFlags & ACCESS_HOST_READ) == ACCESS_HOST_READ)
		ret |= VK_ACCESS_HOST_READ_BIT;

	if ((accessFlags & ACCESS_HOST_WRITE) == ACCESS_HOST_WRITE)
		ret |= VK_ACCESS_HOST_WRITE_BIT;

	if ((accessFlags & ACCESS_MEMORY_READ) == ACCESS_MEMORY_READ)
		ret |= VK_ACCESS_MEMORY_READ_BIT;

	if ((accessFlags & ACCESS_MEMORY_WRITE) == ACCESS_MEMORY_WRITE)
		ret |= VK_ACCESS_MEMORY_WRITE_BIT;

	return ret;
}
