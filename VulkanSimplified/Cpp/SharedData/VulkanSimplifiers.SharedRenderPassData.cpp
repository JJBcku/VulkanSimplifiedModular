module VulkanSimplifiers.SharedRenderPassData;

SharedRenderPassDataSimplifier::SharedRenderPassDataSimplifier(SharedRenderPassDataInternal& ref) : _internal(ref)
{
}

SharedRenderPassDataSimplifier::~SharedRenderPassDataSimplifier()
{
}

IDObject<RenderPassAttachmentData> SharedRenderPassDataSimplifier::AddRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples,
	RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserve)
{
	return _internal.AddRenderPassAttachment(format, samples, loadOP, storeOP, initialLayout, finalLayout, addOnReserve);
}

IDObject<RenderPassAttachmentReference> SharedRenderPassDataSimplifier::AddRenderPassAttachmentReference(std::uint32_t attachmentIndex, ImageLayoutFlags subpassUsedAttachmentLayout,
	size_t addOnReserve)
{
	return _internal.AddRenderPassAttachmentReference(attachmentIndex, subpassUsedAttachmentLayout, addOnReserve);
}

IDObject<SubpassDependencyData> SharedRenderPassDataSimplifier::AddSubpassDependency(std::uint32_t srcSubpass, std::uint32_t dstSubpass, PipelineStageFlags srcStageFlags, PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserve)
{
	return _internal.AddSubpassDependency(srcSubpass, dstSubpass, srcStageFlags, dstStageFlags, srcAccessFlags, dstAccessFlags, addOnReserve);
}
