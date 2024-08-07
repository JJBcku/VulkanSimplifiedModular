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

VulkanDeviceFeatureFlags PhysicalDeviceSimplifier::GetVulkan11Features() const
{
	return _internal.GetVulkan11Features();
}

VulkanDeviceFeatureFlags PhysicalDeviceSimplifier::GetVulkan12Features() const
{
	return _internal.GetVulkan12Features();
}

VulkanDeviceFeatureFlags PhysicalDeviceSimplifier::GetVulkan13Features() const
{
	return _internal.GetVulkan13Features();
}

SurfaceSupportData PhysicalDeviceSimplifier::GetSurfaceSupport(IDObject<WindowPointer> windowID) const
{
	return _internal.GetSurfaceSupport(windowID);
}
