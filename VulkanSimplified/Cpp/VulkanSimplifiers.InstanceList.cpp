module VulkanSimplifiers.InstanceList;

InstanceListSimplifier::InstanceListSimplifier(InstanceListInternal& ref) : _internal(ref)
{
}

InstanceListSimplifier::~InstanceListSimplifier()
{
}

VulkanVersionData InstanceListSimplifier::GetMaxAvailableVulkanVersion() const
{
	return _internal.GetMaxAvailableVulkanVersion();
}
