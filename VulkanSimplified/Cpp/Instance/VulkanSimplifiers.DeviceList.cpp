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

LogicalDeviceSimplifier DeviceListSimplifier::GetLogicalDeviceSimplifier(IDObject<LogicalDevicePointer> deviceID)
{
	return _internal.GetLogicalDeviceSimplifier(deviceID);
}

IDObject<LogicalDevicePointer> DeviceListSimplifier::AddLogicalDevice(const LogicalDeviceCreationInfo& createInfo, size_t addOnReserve)
{
	return _internal.AddLogicalDevice(createInfo, addOnReserve);
}
