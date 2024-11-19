export module VulkanSimplifiers.IRCommandPool;

import VulkanSimplifiers.CommandPool.Internal;

export class IRCommandPoolSimplifier
{
public:
	IRCommandPoolSimplifier(IRCommandPoolInternal& ref);
	~IRCommandPoolSimplifier();

	IRCommandPoolSimplifier& operator=(const IRCommandPoolSimplifier&) noexcept = delete;

private:
	IRCommandPoolInternal& _internal;
};