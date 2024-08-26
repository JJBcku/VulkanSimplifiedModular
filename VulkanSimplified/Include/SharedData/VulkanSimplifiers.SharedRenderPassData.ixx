export module VulkanSimplifiers.SharedRenderPassData;

import VulkanSimplifiers.SharedRenderPassData.Internal;

export class SharedRenderPassDataSimplifier
{
public:
	SharedRenderPassDataSimplifier(SharedRenderPassDataInternal& ref);
	~SharedRenderPassDataSimplifier();

	SharedRenderPassDataSimplifier& operator=(const SharedRenderPassDataSimplifier&) noexcept = delete;

private:
	SharedRenderPassDataInternal& _internal;
};