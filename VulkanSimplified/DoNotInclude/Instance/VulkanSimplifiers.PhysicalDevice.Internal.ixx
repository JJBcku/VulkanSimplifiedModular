module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.PhysicalDevice.Internal;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.PhysicalDevice.Data;
import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.WindowList.Data;

import VulkanSimplifiers.Common.DeviceFeatureFlags;
import VulkanSimplifiers.Common.DataFormatFlags.Internal;

struct QueueSupportSavedData
{
	VkSurfaceKHR surface;
	SurfaceSupportData queueData;

	QueueSupportSavedData();
	QueueSupportSavedData(VkSurfaceKHR initSurface, const SurfaceSupportData& initQueueData);
};

export class PhysicalDeviceInternal
{
public:
	PhysicalDeviceInternal(VkPhysicalDevice physicalDevice, std::uint32_t instanceVulkanVersion, WindowListInternal& windowList);
	~PhysicalDeviceInternal();

	PhysicalDeviceInternal(const PhysicalDeviceInternal&) noexcept = default;

	PhysicalDeviceInternal& operator=(const PhysicalDeviceInternal&) noexcept = delete;

	DeviceVulkanPropertiesSimplified GetVulkanPropertiesSimplified() const;

	VulkanDeviceFeatureFlags GetVulkan10Features() const;

	VkPhysicalDevice GetPhysicalDevice() const;

	SurfaceSupportData GetSurfaceSupport(IDObject<WindowPointer> windowID);

private:
	VkPhysicalDevice _physicalDevice;
	DeviceVulkanPropertiesSimplified _vulkanProperties;

	VulkanDeviceFeatureFlags _device10features;

	WindowListInternal& _windowList;

	DeviceType GetDeviceType(const VkPhysicalDeviceType& deviceType) const;

	Vulkan10DeviceLimits CompileVulkan10DeviceLimits(const VkPhysicalDeviceLimits& deviceLimits) const;

	VulkanDeviceFeatureFlags CompileVulkan10DeviceFeatures(const VkPhysicalDeviceFeatures& deviceFeatures) const;

	DeviceExtensionFlags CompileKHRDeviceExtensionList(const std::vector<VkExtensionProperties>& availableExtensions) const;

	FormatsSupportedFullFeatures CompileFormatsSupportedFeatures() const;

	void GetFirstSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& optimalImageFeatureList, DataFormatFirstFlagSetBits flagSetBit) const;
	void GetSecondSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& optimalImageFeatureList, DataFormatSecondFlagSetBits flagSetBit) const;
	void GetThirdSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& optimalImageFeatureList, DataFormatThirdFlagSetBits flagSetBit) const;
	void GetFourthSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& optimalImageFeatureList, DataFormatFourthFlagSetBits flagSetBit) const;
	void GetFifthSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& optimalImageFeatureList, DataFormatFifthFlagSetBits flagSetBit) const;
	void GetSixthSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& optimalImageFeatureList, DataFormatSixthFlagSetBits flagSetBit) const;
	void GetSeventhSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& optimalImageFeatureList, DataFormatSeventhFlagSetBits flagSetBit) const;
};