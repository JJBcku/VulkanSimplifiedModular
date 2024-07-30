export module VulkanSimplifiers.Instance;

import VulkanSimplifiers.Instance.Internal;

export class InstanceSimplifier
{
public:
	InstanceSimplifier(InstanceInternal& ref);
	~InstanceSimplifier();

	InstanceSimplifier& operator=(const InstanceSimplifier&) noexcept = delete;

private:
	InstanceInternal& _internal;
};