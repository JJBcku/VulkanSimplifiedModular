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

void PrimaryIRCommandBufferSimplifier::TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs,
	std::uint32_t imagesIndex)
{
	_internal.TransitionSwapchainImageToTrasferDestination(windowID, queuesIDs, imagesIndex);
}

void PrimaryIRCommandBufferSimplifier::TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs,
	std::uint32_t imagesIndex)
{
	_internal.TransitionSwapchainImageToPresent(windowID, queuesIDs, imagesIndex);
}

void PrimaryIRCommandBufferSimplifier::BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<AutoCleanup2DSimpleImage> imageID, std::uint32_t startX, std::uint32_t startY,
	std::uint32_t width, std::uint32_t height, std::uint32_t swapchainImageIndex)
{
	_internal.BlitToSwapchainImage(windowID, imageID, startX, startY, width, height, swapchainImageIndex);
}