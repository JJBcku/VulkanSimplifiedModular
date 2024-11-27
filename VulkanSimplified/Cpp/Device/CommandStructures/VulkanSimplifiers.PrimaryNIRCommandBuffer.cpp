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

void PrimaryNIRCommandBufferSimplifier::TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs,
	std::uint32_t imagesIndex)
{
	_internal.TransitionSwapchainImageToTrasferDestination(windowID, queuesIDs, imagesIndex);
}

void PrimaryNIRCommandBufferSimplifier::TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<std::pair<size_t, size_t>> queuesIDs,
	std::uint32_t imagesIndex)
{
	_internal.TransitionSwapchainImageToPresent(windowID, queuesIDs, imagesIndex);
}

void PrimaryNIRCommandBufferSimplifier::BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<AutoCleanup2DSimpleImage> imageID, std::uint32_t startX, std::uint32_t startY,
	std::uint32_t width, std::uint32_t height, std::uint32_t swapchainImageIndex)
{
	_internal.BlitToSwapchainImage(windowID, imageID, startX, startY, width, height, swapchainImageIndex);
}