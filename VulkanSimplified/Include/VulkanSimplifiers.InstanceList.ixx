export module VulkanSimplifiers.InstanceList;

import VulkanSimplifiers.InstanceList.Internal;
import VulkanSimplifiers.Common.VulkanVersionData;

export class InstanceListSimplifier
{
public:
	InstanceListSimplifier(InstanceListInternal& ref);
	~InstanceListSimplifier();

	InstanceListSimplifier& operator=(const InstanceListSimplifier&) noexcept = delete;

	VulkanVersionData GetMaxAvailableVulkanVersion() const;

private:
	InstanceListInternal& _internal;
};