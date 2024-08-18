export module VulkanSimplifiers.Main.Data;
export import VulkanSimplifiers.EventHandling.Data;

export import VulkanSimplifiers.Common.VulkanVersionData;
export import VulkanSimplifiers.SharedDataList.CreationData;
import VulkanSimplifiers.Instance.Internal;

import ListTemplates.IDObject;
import VulkanSimplifiers.WindowList.Data;

import std;

export struct MainSimplifierInitData
{
	std::string appName;
	std::string appVariantName;
	VulkanVersionData appVersion;
	std::string engineName;
	VulkanVersionData engineVersion;
	EventHandlerInitData eventHandlerData;
	size_t windowsListInitialCapacity;

	SharedDataListCreationData sharedDataListInitData;

	MainSimplifierInitData();
};

export typedef std::uint64_t InstanceExtensionList;

export enum VulkanInstanceExtensionFlags : InstanceExtensionList
{
	SWAPCHAIN_EXTENDED_COLORSPACE = 0x1,
};

export struct InstanceCreationInfo
{
	VulkanVersionData usedVulkanApiVersion;
	InstanceExtensionList requestedExtensions;
	std::optional<IDObject<WindowPointer>> windowExampleID;
	size_t logicalDeviceListInitialCapacity;

	InstanceCreationInfo();
};