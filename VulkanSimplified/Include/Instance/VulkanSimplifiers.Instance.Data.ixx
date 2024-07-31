export module VulkanSimplifiers.Instance.Data;

import std;
import ListTemplates.IDObject;
import VulkanSimplifiers.Common.VulkanVersionData;
import VulkanSimplifiers.WindowList.Data;

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
	size_t logicalDeviceListInitialCapacity;

	InstanceInitInfo();
};