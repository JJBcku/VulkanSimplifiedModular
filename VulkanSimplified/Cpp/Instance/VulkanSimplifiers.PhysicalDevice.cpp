module VulkanSimplifiers.PhysicalDevice;

PhysicalDeviceSimplifier::PhysicalDeviceSimplifier(PhysicalDeviceInternal& ref) : _internal(ref)
{
}

PhysicalDeviceSimplifier::~PhysicalDeviceSimplifier()
{
}

DeviceVulkanPropertiesSimplified PhysicalDeviceSimplifier::GetVulkanPropertiesSimplified() const
{
	return _internal.GetVulkanPropertiesSimplified();
}

VulkanDeviceFeatureFlags PhysicalDeviceSimplifier::GetVulkan10Features() const
{
	return _internal.GetVulkan10Features();
}

SurfaceSupportData PhysicalDeviceSimplifier::GetSurfaceSupport(IDObject<WindowPointer> windowID) const
{
	return _internal.GetSurfaceSupport(windowID);
}

MemoryHeapList PhysicalDeviceSimplifier::GetDeviceMemoryData() const
{
	return _internal.GetDeviceMemoryData();
}
