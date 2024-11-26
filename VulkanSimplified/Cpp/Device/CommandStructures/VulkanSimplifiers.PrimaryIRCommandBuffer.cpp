module VulkanSimplifiers.PrimaryIRCommandBuffer;

PrimaryIRCommandBufferSimplifier::PrimaryIRCommandBufferSimplifier(PrimaryIRCommandBufferInternal& ref) : CommonCommandBuffer(ref), _internal(ref)
{
}

PrimaryIRCommandBufferSimplifier::~PrimaryIRCommandBufferSimplifier()
{
}

void PrimaryIRCommandBufferSimplifier::BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID,
	std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues,
	bool usesSecondaryBuffers)
{
	_internal.BeginRenderPass(renderPassID, framebufferID, startX, startY, width, height, clearValues, usesSecondaryBuffers);
}

void PrimaryIRCommandBufferSimplifier::EndRenderPass()
{
	_internal.EndRenderPass();
}

void PrimaryIRCommandBufferSimplifier::ResetCommandBuffer(bool freeResources)
{
	_internal.ResetCommandBuffer(freeResources);
}