module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DeviceRenderPassData.Data;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.SharedRenderPassData.Data;

export class AutoCleanupRenderPass;

export typedef std::optional<IDObject<RenderPassAttachmentReference>> ARef;

export struct SubpassCreationDataNoResolve
{
	std::vector<ARef> inputAttachments;
	std::vector<ARef> colorAttachments;
	ARef depthStencilAttachment;
	std::vector<std::uint32_t> preserveAttachment;

	SubpassCreationDataNoResolve() = default;
};

export struct SubpassCreationDataResolve
{
	std::vector<ARef> inputAttachments;
	std::vector<std::pair<ARef, ARef>> colorAttachments;
	ARef depthStencilAttachment;
	std::vector<std::uint32_t> preserveAttachment;

	SubpassCreationDataResolve() = default;
};