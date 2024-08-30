module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DeviceRenderPassData.Internal;

DeviceRenderPassDataInternal::DeviceRenderPassDataInternal(const DeviceRenderPassCreationData& creationData, const SharedRenderPassDataInternal& sharedData, VkDevice device) :
	_sharedData(sharedData), _device(device), _renderPasses(creationData.renderPassesInitialCapacity)
{
}

DeviceRenderPassDataInternal::~DeviceRenderPassDataInternal()
{
}

IDObject<AutoCleanupRenderPass> DeviceRenderPassDataInternal::AddRenderPassWithoutResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
	const std::vector<SubpassCreationDataNoResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve)
{
	VkRenderPass add = VK_NULL_HANDLE;
	VkRenderPassCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

	std::vector<VkAttachmentDescription> attachmentData;

	if (!attachments.empty())
	{
		attachmentData = _sharedData.GetRenderPassAttachmentDescriptors(attachments);
		createInfo.attachmentCount = static_cast<std::uint32_t>(attachmentData.size());
		createInfo.pAttachments = attachmentData.data();
	}

	std::vector<VkSubpassDescription> subpassDataList;
	std::vector<std::vector<VkAttachmentReference>> inputAttachments;
	std::vector<std::vector<VkAttachmentReference>> colorAttachments;
	std::vector<std::optional<VkAttachmentReference>> depthStencilAttachments;

	if (!subpasses.empty())
	{
		subpassDataList.reserve(subpasses.size());
		inputAttachments.resize(subpasses.size());
		colorAttachments.resize(subpasses.size());
		depthStencilAttachments.resize(subpasses.size());

		for (size_t i = 0; i < subpasses.size(); i++)
		{
			VkSubpassDescription subpassAdd{};
			subpassAdd.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			
			if (!subpasses[i].inputAttachments.empty())
			{
				inputAttachments[i] = _sharedData.GetRenderPassAttachmentReferences(subpasses[i].inputAttachments);
				subpassAdd.inputAttachmentCount = static_cast<std::uint32_t>(inputAttachments[i].size());
				subpassAdd.pInputAttachments = inputAttachments[i].data();
			}

			if (!subpasses[i].colorAttachments.empty())
			{
				colorAttachments[i] = _sharedData.GetRenderPassAttachmentReferences(subpasses[i].colorAttachments);
				subpassAdd.colorAttachmentCount = static_cast<std::uint32_t>(colorAttachments[i].size());
				subpassAdd.pColorAttachments = colorAttachments[i].data();
			}

			if (subpasses[i].depthStencilAttachment.has_value())
			{
				depthStencilAttachments[i] = _sharedData.GetRenderPassAttachmentReference(subpasses[i].depthStencilAttachment);
				subpassAdd.pDepthStencilAttachment = &depthStencilAttachments[i].value();
			}

			if (!subpasses[i].preserveAttachment.empty())
			{
				subpassAdd.preserveAttachmentCount = static_cast<std::uint32_t>(subpasses[i].preserveAttachment.size());
				subpassAdd.pPreserveAttachments = subpasses[i].preserveAttachment.data();
			}

			subpassDataList.push_back(subpassAdd);
		}

		createInfo.subpassCount = static_cast<std::uint32_t>(subpassDataList.size());
		createInfo.pSubpasses = subpassDataList.data();
	}

	std::vector<VkSubpassDependency> subpassDependenciesData;

	if (!subpassDependencies.empty())
	{
		subpassDependenciesData = _sharedData.GetSubpassDependencies(subpassDependencies);
		createInfo.dependencyCount = static_cast<std::uint32_t>(subpassDependenciesData.size());
		createInfo.pDependencies = subpassDependenciesData.data();
	}

	if (vkCreateRenderPass(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("DeviceRenderPassDataInternal::AddRenderPassWithoutResolveAttachments Error: Program failed to create the render pass!");

	return _renderPasses.AddObject(AutoCleanupRenderPass(_device, add), addOnReserve);
}

IDObject<AutoCleanupRenderPass> DeviceRenderPassDataInternal::AddRenderPassWithResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments, const std::vector<SubpassCreationDataResolve>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve)
{
	VkRenderPass add = VK_NULL_HANDLE;
	VkRenderPassCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

	std::vector<VkAttachmentDescription> attachmentData;

	if (!attachments.empty())
	{
		attachmentData = _sharedData.GetRenderPassAttachmentDescriptors(attachments);
		createInfo.attachmentCount = static_cast<std::uint32_t>(attachmentData.size());
		createInfo.pAttachments = attachmentData.data();
	}

	std::vector<VkSubpassDescription> subpassDataList;
	std::vector<std::vector<VkAttachmentReference>> inputAttachments;
	std::vector<std::vector<VkAttachmentReference>> colorAttachments;
	std::vector<std::vector<VkAttachmentReference>> resolveAttachments;
	std::vector<std::optional<VkAttachmentReference>> depthStencilAttachments;

	if (!subpasses.empty())
	{
		subpassDataList.reserve(subpasses.size());
		inputAttachments.resize(subpasses.size());
		colorAttachments.resize(subpasses.size());
		resolveAttachments.resize(subpasses.size());
		depthStencilAttachments.resize(subpasses.size());

		for (size_t i = 0; i < subpasses.size(); i++)
		{
			VkSubpassDescription subpassAdd{};
			subpassAdd.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

			if (!subpasses[i].inputAttachments.empty())
			{
				inputAttachments[i] = _sharedData.GetRenderPassAttachmentReferences(subpasses[i].inputAttachments);
				subpassAdd.inputAttachmentCount = static_cast<std::uint32_t>(inputAttachments[i].size());
				subpassAdd.pInputAttachments = inputAttachments[i].data();
			}

			if (!subpasses[i].colorAttachments.empty())
			{
				colorAttachments[i].resize(subpasses[i].colorAttachments.size());
				resolveAttachments[i].resize(subpasses[i].colorAttachments.size());

				for (size_t j = 0; j < subpasses[i].colorAttachments.size(); j++)
				{
					colorAttachments[i][j] = _sharedData.GetRenderPassAttachmentReference(subpasses[i].colorAttachments[j].first);
					resolveAttachments[i][j] = _sharedData.GetRenderPassAttachmentReference(subpasses[i].colorAttachments[j].second);
				}

				subpassAdd.colorAttachmentCount = static_cast<std::uint32_t>(colorAttachments[i].size());
				subpassAdd.pColorAttachments = colorAttachments[i].data();
				subpassAdd.pResolveAttachments = resolveAttachments[i].data();
			}

			if (subpasses[i].depthStencilAttachment.has_value())
			{
				depthStencilAttachments[i] = _sharedData.GetRenderPassAttachmentReference(subpasses[i].depthStencilAttachment);
				subpassAdd.pDepthStencilAttachment = &depthStencilAttachments[i].value();
			}

			if (!subpasses[i].preserveAttachment.empty())
			{
				subpassAdd.preserveAttachmentCount = static_cast<std::uint32_t>(subpasses[i].preserveAttachment.size());
				subpassAdd.pPreserveAttachments = subpasses[i].preserveAttachment.data();
			}

			subpassDataList.push_back(subpassAdd);
		}

		createInfo.subpassCount = static_cast<std::uint32_t>(subpassDataList.size());
		createInfo.pSubpasses = subpassDataList.data();
	}

	std::vector<VkSubpassDependency> subpassDependenciesData;

	if (!subpassDependencies.empty())
	{
		subpassDependenciesData = _sharedData.GetSubpassDependencies(subpassDependencies);
		createInfo.dependencyCount = static_cast<std::uint32_t>(subpassDependenciesData.size());
		createInfo.pDependencies = subpassDependenciesData.data();
	}

	if (vkCreateRenderPass(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("DeviceRenderPassDataInternal::AddRenderPassWithResolveAttachments Error: Program failed to create the render pass!");

	return _renderPasses.AddObject(AutoCleanupRenderPass(_device, add), addOnReserve);
}

VkRenderPass DeviceRenderPassDataInternal::GetRenderPass(IDObject<AutoCleanupRenderPass> renderPassID) const
{
	return _renderPasses.GetConstObject(renderPassID).GetRenderPass();
}
