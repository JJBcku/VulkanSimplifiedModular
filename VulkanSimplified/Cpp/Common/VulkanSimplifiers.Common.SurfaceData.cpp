module VulkanSimplifiers.Common.SurfaceData;

SurfaceSupportedColorspaceFormatsLists::SurfaceSupportedColorspaceFormatsLists()
{
}

SurfaceSupportData::SurfaceSupportData()
{
	minImageCount = 0;
	maxImageCount = 0;

	surfaceUsageFlags = 0;
	surfacePresentModes = 0;
}

SwapchainCreationData::SwapchainCreationData()
{
	swapchainUsage = static_cast<SwapchainUsage>(0);
	surfacePresentMode = static_cast<SurfacePresentModeBits>(0);

	imageAmount = 0;
	padding = 0;
}