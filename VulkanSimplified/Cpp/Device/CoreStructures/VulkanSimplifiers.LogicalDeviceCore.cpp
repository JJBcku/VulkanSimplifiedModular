module VulkanSimplifiers.LogicalDeviceCore;

LogicalDeviceCoreSimplifier::LogicalDeviceCoreSimplifier(LogicalDeviceCoreInternal& ref) : _internal(ref)
{
}

LogicalDeviceCoreSimplifier::~LogicalDeviceCoreSimplifier()
{
}

void LogicalDeviceCoreSimplifier::CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected,
	bool throwOnSwapchainExist, bool throwOnDeviceChange)
{
	_internal.CreateSwapchain(windowID, surfaceCreateInfo, createProtected, throwOnSwapchainExist, throwOnDeviceChange);
}

void LogicalDeviceCoreSimplifier::WaitIdle()
{
	_internal.WaitIdle();
}
