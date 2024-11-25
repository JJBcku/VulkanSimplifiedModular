module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DeviceRenderPassData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.DeviceRenderPassData.CreationData;
import VulkanSimplifiers.DeviceRenderPassData.InternalData;
import VulkanSimplifiers.DeviceRenderPassData.Data;

import VulkanSimplifiers.SharedRenderPassData.Internal;
import VulkanSimplifiers.SharedRenderPassData.Data;

export class DeviceRenderPassDataInternal
{
public:
	DeviceRenderPassDataInternal(const DeviceRenderPassCreationData& creationData, const SharedRenderPassDataInternal& sharedData, VkDevice device);
	~DeviceRenderPassDataInternal();

	DeviceRenderPassDataInternal& operator=(const DeviceRenderPassDataInternal&) noexcept = delete;

	IDObject<AutoCleanupRenderPass> AddRenderPassWithoutResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
		const std::vector<SubpassCreationDataNoResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve);

	IDObject<AutoCleanupRenderPass> AddRenderPassWithResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
		const std::vector<SubpassCreationDataResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve);

	VkRenderPass GetRenderPass(IDObject<AutoCleanupRenderPass> renderPassID) const;

private:
	const SharedRenderPassDataInternal& _sharedData;
	VkDevice _device;

	UnsortedList<AutoCleanupRenderPass> _renderPasses;
};