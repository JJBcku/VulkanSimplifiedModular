export module VulkanSimplifiers.SharedRenderPassData.CreationData;

export struct SharedRenderPassDataCreationInfo
{
	size_t sharedRenderPassAttachmentsInitialCapacity;
	size_t sharedRenderPassReferencesInitialCapacity;

	SharedRenderPassDataCreationInfo();
};