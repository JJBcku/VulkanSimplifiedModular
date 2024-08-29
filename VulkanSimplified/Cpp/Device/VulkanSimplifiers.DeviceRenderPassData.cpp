module VulkanSimplifiers.DeviceRenderPassData;

DeviceRenderPassDataSimplifier::DeviceRenderPassDataSimplifier(DeviceRenderPassDataInternal& ref) : _internal(ref)
{
}

DeviceRenderPassDataSimplifier::~DeviceRenderPassDataSimplifier()
{
}

IDObject<AutoCleanupRenderPass> DeviceRenderPassDataSimplifier::AddRenderPassWithoutResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
	const std::vector<SubpassCreationDataNoResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve)
{
	return _internal.AddRenderPassWithoutResolveAttachments(attachments, subpasses, subpassDependencies, addOnReserve);
}

IDObject<AutoCleanupRenderPass> DeviceRenderPassDataSimplifier::AddRenderPassWithResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
	const std::vector<SubpassCreationDataResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve)
{
	return _internal.AddRenderPassWithResolveAttachments(attachments, subpasses, subpassDependencies, addOnReserve);
}
