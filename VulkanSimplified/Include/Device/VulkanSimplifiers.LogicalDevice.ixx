export module VulkanSimplifiers.LogicalDevice;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.LogicalDevice.Internal;
import VulkanSimplifiers.WindowList.Data;
import VulkanSimplifiers.Window.InternalData;
import VulkanSimplifiers.Common.SurfaceData;

export class LogicalDeviceSimplifier
{
public:
	LogicalDeviceSimplifier(LogicalDeviceInternal& ref);
	~LogicalDeviceSimplifier();

	LogicalDeviceSimplifier& operator=(const LogicalDeviceSimplifier&) noexcept = delete;

	void CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected, bool throwOnSwapchainExist, bool throwOnDeviceChange);

private:
	LogicalDeviceInternal& _internal;
};