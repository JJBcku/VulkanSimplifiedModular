module VulkanSimplifiers.LogicalDevice.Data;

QueueCreateInfo::QueueCreateInfo()
{
	queueFamily = 0;
	queuePriority = 1.0f;
	queueCreationFlags = 0;
}

RequestedExtensionList::RequestedExtensionList()
{
	khrExtensions = 0;
}

LogicalDeviceCreationInfo::LogicalDeviceCreationInfo()
{
	physicalGPUIndex = std::numeric_limits<size_t>::max();

	vulkan10Features = 0;
	vulkan11Features = 0;
	vulkan12Features = 0;
	vulkan13Features = 0;
}