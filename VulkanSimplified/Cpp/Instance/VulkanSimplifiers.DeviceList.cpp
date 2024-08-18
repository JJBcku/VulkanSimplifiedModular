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

LogicalDeviceMainSimplifier DeviceListSimplifier::GetLogicalDeviceMainSimplifier(IDObject<LogicalDevicePointer> deviceID)
{
	return _internal.GetLogicalDeviceMainSimplifier(deviceID);
}

IDObject<LogicalDevicePointer> DeviceListSimplifier::AddLogicalDevice(const LogicalDeviceCreationInfo& createInfo, const DeviceMainCreationData& mainCreationData, size_t addOnReserve)
{
	return _internal.AddLogicalDevice(createInfo, mainCreationData, addOnReserve);
}
