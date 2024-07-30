export module VulkanSimplifiers.Instance.Data;

import std;
import ListTemplates.IDObject;
import VulkanSimplifiers.Common.VulkanVersionData;
import VulkanSimplifiers.WindowList.Data;

export typedef std::uint64_t InstanceExtensionList;

export enum VulkanInstanceExtensionFlags : InstanceExtensionList
{
	SWAPCHAIN_EXTENDED_COLORSPACE = 0x1,
};

export struct InstanceInitInfo
{
	std::string appName;
	std::uint32_t appVersion;
	std::uint32_t padding;
	std::string engineName;
	std::uint32_t engineVersion;
	std::uint32_t usedVulkanApiVersion;
	std::vector<const char*> requestedExtensions;
	std::vector<const char*> requestedLayers;

	InstanceInitInfo() = default;
};