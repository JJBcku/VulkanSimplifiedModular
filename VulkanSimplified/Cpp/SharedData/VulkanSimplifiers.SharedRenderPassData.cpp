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

IDObject<RenderPassDoubleColorClearValues> SharedRenderPassDataSimplifier::AddDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserve)
{
	return _internal.AddDoubleColorClearValue(r, g, b, a, addOnReserve);
}

IDObject<RenderPassInt64ColorClearValues> SharedRenderPassDataSimplifier::AddInt64ColorClearValue(std::int64_t r, std::int64_t g, std::int64_t b, std::int64_t a, size_t addOnReserve)
{
	return _internal.AddInt64ColorClearValue(r, g, b, a, addOnReserve);
}

IDObject<RenderPassUInt64ColorClearValues> SharedRenderPassDataSimplifier::AddUInt64ColorClearValue(std::uint64_t r, std::uint64_t g, std::uint64_t b, std::uint64_t a, size_t addOnReserve)
{
	return _internal.AddUInt64ColorClearValue(r, g, b, a, addOnReserve);
}

IDObject<RenderPassFloatColorClearValues> SharedRenderPassDataSimplifier::AddFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserve)
{
	return _internal.AddFloatColorClearValue(r, g, b, a, addOnReserve);
}

IDObject<RenderPassIntColorClearValues> SharedRenderPassDataSimplifier::AddIntColorClearValue(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a, size_t addOnReserve)
{
	return _internal.AddIntColorClearValue(r, g, b, a, addOnReserve);
}

IDObject<RenderPassUIntColorClearValues> SharedRenderPassDataSimplifier::AddUIntColorClearValue(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a, size_t addOnReserve)
{
	return _internal.AddUIntColorClearValue(r, g, b, a, addOnReserve);
}

IDObject<RenderPassDepthStencilClearValues> SharedRenderPassDataSimplifier::AddDepthStencilClearValue(float depth, std::uint32_t stencil, size_t addOnReserve)
{
	return _internal.AddDepthStencilClearValue(depth, stencil, addOnReserve);
}
