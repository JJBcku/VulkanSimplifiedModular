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