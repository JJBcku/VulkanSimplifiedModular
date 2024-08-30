export module VulkanSimplifiers.Common.SurfaceData;

import std;

export import VulkanSimplifiers.Common.ImageUsageFlags;
export import VulkanSimplifiers.Common.DataFormatFlags;

export import VulkanSimplifiers.Window.Data;

export typedef std::uint64_t SurfacePresentModes;

export enum SurfacePresentModeBits : SurfacePresentModes
{
	PRESENT_MODE_IMMEDIATE = 0x1,
	PRESENT_MODE_MAILBOX = 0x2,
	PRESENT_MODE_FIFO_STRICT = 0x4,
	PRESENT_MODE_FIFO_RELAXED = 0x8,
};

export struct SurfaceSupportedColorspaceFormatsLists
{
	DataFormatFullSet srgbNonlinearColorspace;

	SurfaceSupportedColorspaceFormatsLists();
};

export struct SurfaceSupportData
{
	std::vector<bool> queuePresentingSupport;

	std::uint32_t minImageCount;
	std::uint32_t maxImageCount;

	ImageUsageFlags surfaceUsageFlags;
	SurfacePresentModes surfacePresentModes;
	SurfaceSupportedColorspaceFormatsLists surfaceSupportedSwapchainFormats;

	SurfaceSupportData();
};

export struct SwapchainCreationData
{
	SwapchainUsage swapchainUsage;
	SurfacePresentModeBits surfacePresentMode;
	DataFormatSetIndependentID format;

	std::uint32_t imageAmount;
	std::uint32_t padding;

	std::vector<size_t> queuesUsingSwapchain;

	SwapchainCreationData();
};
