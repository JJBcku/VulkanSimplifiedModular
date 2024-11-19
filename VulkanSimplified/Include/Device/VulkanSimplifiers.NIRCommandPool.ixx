export module VulkanSimplifiers.NIRCommandPool;

import VulkanSimplifiers.CommandPool.Internal;

export class NIRCommandPoolSimplifier
{
public:
	NIRCommandPoolSimplifier(NIRCommandPoolInternal& ref);
	~NIRCommandPoolSimplifier();

	NIRCommandPoolSimplifier& operator=(const NIRCommandPoolSimplifier&) noexcept = delete;

private:
	NIRCommandPoolInternal& _internal;
};