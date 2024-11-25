module VulkanSimplifiers.LogicalDeviceCore.CreationData;

QueueCreateInfo::QueueCreateInfo()
{
	queueFamily = 0;
	queuePriority = 1.0f;
}

LogicalDeviceCreationInfo::LogicalDeviceCreationInfo()
{
	physicalGPUIndex = std::numeric_limits<size_t>::max();

	vulkan10Features = 0;
}