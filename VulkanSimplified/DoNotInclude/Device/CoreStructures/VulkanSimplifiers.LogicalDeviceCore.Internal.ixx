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
	std::uint32_t GetQueueFamily(size_t queueID) const;

	size_t GetQueueFamiliesCount() const;

	VkQueue GetQueue(size_t queueID) const;

	void CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected, bool throwOnSwapchainExist, bool throwOnDeviceChange);

	void WaitIdle();

private:
	WindowListInternal& _windowList;

	VkDevice _logicalDevice;
	VkPhysicalDevice _physicalDevice;
	std::string _physicalDeviceName;
	std::string _logicalDeviceName;
	std::uint32_t _apiVersion;
	std::uint32_t _padding;
	size_t _queueFamiliesCount;
	std::vector<std::pair<VkQueue, std::uint32_t>> _queues;

	VkPhysicalDeviceFeatures CompileRequestedVulkan10Features(VulkanDeviceFeatureFlags featureFlags);

	std::vector<const char*> CompileRequestedExtensions(const DeviceExtensionList& deviceExtensionList) const;

	void CompileRequestedKHRExtensions(std::vector<const char*>& requiredExtensions, DeviceExtensionFlags khrExtensions) const;

	VkPresentModeKHR TranslatePresentMode(SurfacePresentModeBits presentMode) const;
};