module VulkanSimplifiers.Instance;

InstanceSimplifier::InstanceSimplifier(InstanceInternal& ref) : _internal(ref)
{
}

InstanceSimplifier::~InstanceSimplifier()
{
}

DeviceListSimplifier InstanceSimplifier::GetDeviceListSimplifier()
{
	return _internal.GetDeviceListSimplifier();
}
