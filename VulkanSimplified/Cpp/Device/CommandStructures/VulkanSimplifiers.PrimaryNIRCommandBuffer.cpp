module VulkanSimplifiers.PrimaryNIRCommandBuffer;

PrimaryNIRCommandBufferSimplifier::PrimaryNIRCommandBufferSimplifier(PrimaryNIRCommandBufferInternal& ref) : CommonCommandBuffer(ref), _internal(ref)
{
}

PrimaryNIRCommandBufferSimplifier::~PrimaryNIRCommandBufferSimplifier()
{
}

void PrimaryNIRCommandBufferSimplifier::BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID,
	std::uint32_t startX, std::uint32_t startY, std::uint32_t width, std::uint32_t height, const std::vector<std::optional<RenderPassClearValuesID>>& clearValues,
	bool usesSecondaryBuffers)
{
	_internal.BeginRenderPass(renderPassID, framebufferID, startX, startY, width, height, clearValues, usesSecondaryBuffers);
}

void PrimaryNIRCommandBufferSimplifier::EndRenderPass()
{
	_internal.EndRenderPass();
}