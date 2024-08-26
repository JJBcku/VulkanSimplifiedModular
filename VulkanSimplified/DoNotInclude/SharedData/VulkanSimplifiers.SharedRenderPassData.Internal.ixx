export module VulkanSimplifiers.SharedRenderPassData.Internal;

import VulkanSimplifiers.SharedRenderPassData.CreationData;

export class SharedRenderPassDataInternal
{
public:
	SharedRenderPassDataInternal(const SharedRenderPassDataCreationInfo& creationData);
	~SharedRenderPassDataInternal();

private:
	long long int stump;
};