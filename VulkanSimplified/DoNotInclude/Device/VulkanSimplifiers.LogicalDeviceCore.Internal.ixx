module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.LogicalDeviceCore.Internal;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.LogicalDeviceCore.Data;
import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.WindowList.Data;
import VulkanSimplifiers.Window.InternalData;
import VulkanSimplifiers.Window.Internal;

import VulkanSimplifiers.ShaderList.Internal;
import VulkanSimplifiers.LogicalDeviceCore.InternalData;

import VulkanSimplifiers.Common.DataFormatFlags.Internal;

export class LogicalDeviceCoreInternal
{
public:
	LogicalDeviceCoreInternal(const LogicalDeviceInitData& initData, WindowListInternal& windowList);
	~LogicalDeviceCoreInternal();

	LogicalDeviceCoreInternal(const LogicalDeviceCoreInternal&) noexcept = delete;

	LogicalDeviceCoreInternal& operator=(const LogicalDeviceCoreInternal&) noexcept = delete;

	VkDevice GetDevice() const;
	std::vector<std::uint32_t> GetQueueFamilies(const std::vector<size_t>& queueIDs) const;

	void CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected, bool throwOnSwapchainExist, bool throwOnDeviceChange);

private:
	WindowListInternal& _windowList;

	VkDevice _logicalDevice;
	VkPhysicalDevice _physicalDevice;
	std::string _physicalDeviceName;
	std::string _logicalDeviceName;
	std::uint32_t _apiVersion;
	std::uint32_t _padding;
	std::vector<std::pair<VkQueue, std::uint32_t>> _queues;

	VkPhysicalDeviceFeatures CompileRequestedVulkan10Features(VulkanDeviceFeatureFlags featureFlags);

	std::vector<const char*> CompileRequestedExtensions(const DeviceExtensionList& deviceExtensionList) const;

	void CompileRequestedKHRExtensions(std::vector<const char*>& requiredExtensions, DeviceExtensionFlags khrExtensions) const;

	VkPresentModeKHR TranslatePresentMode(SurfacePresentModeBits presentMode) const;
};