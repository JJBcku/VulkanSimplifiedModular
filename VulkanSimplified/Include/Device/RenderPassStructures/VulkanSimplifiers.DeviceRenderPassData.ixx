export module VulkanSimplifiers.DeviceRenderPassData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.DeviceRenderPassData.Internal;
import VulkanSimplifiers.DeviceRenderPassData.Data;

export class DeviceRenderPassDataSimplifier
{
public:
	DeviceRenderPassDataSimplifier(DeviceRenderPassDataInternal& ref);
	~DeviceRenderPassDataSimplifier();

	DeviceRenderPassDataSimplifier& operator=(const DeviceRenderPassDataSimplifier&) noexcept = delete;

	IDObject<AutoCleanupRenderPass> AddRenderPassWithoutResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
		const std::vector<SubpassCreationDataNoResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve = 0);

	IDObject<AutoCleanupRenderPass> AddRenderPassWithResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
		const std::vector<SubpassCreationDataResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve = 0);

private:
	DeviceRenderPassDataInternal& _internal;
};