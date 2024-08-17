module VulkanSimplifiers.LogicalDevice;

LogicalDeviceSimplifier::LogicalDeviceSimplifier(LogicalDeviceInternal& ref) : _internal(ref)
{
}

LogicalDeviceSimplifier::~LogicalDeviceSimplifier()
{
}

void LogicalDeviceSimplifier::CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected,
	bool throwOnSwapchainExist, bool throwOnDeviceChange)
{
	_internal.CreateSwapchain(windowID, surfaceCreateInfo, createProtected, throwOnSwapchainExist, throwOnDeviceChange);
}
