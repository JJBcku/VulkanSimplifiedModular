module VulkanSimplifiers.DeviceList;

DeviceListSimplifier::DeviceListSimplifier(DeviceListInternal& ref) : _internal(ref)
{
}

DeviceListSimplifier::~DeviceListSimplifier()
{
}

size_t DeviceListSimplifier::GetPhysicalDeviceListSize() const
{
	return _internal.GetPhysicalDeviceListSize();
}

PhysicalDeviceSimplifier DeviceListSimplifier::GetPhysicalDeviceSimplifier(size_t deviceIndex)
{
	return _internal.GetPhysicalDeviceSimplifier(deviceIndex);
}
