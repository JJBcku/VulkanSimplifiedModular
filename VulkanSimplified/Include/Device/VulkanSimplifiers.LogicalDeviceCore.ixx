export module VulkanSimplifiers.LogicalDeviceCore;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.LogicalDeviceCore.Internal;
import VulkanSimplifiers.WindowList.Data;
import VulkanSimplifiers.Window.InternalData;
import VulkanSimplifiers.Common.SurfaceData;

export class LogicalDeviceCoreSimplifier
{
public:
	LogicalDeviceCoreSimplifier(LogicalDeviceCoreInternal& ref);
	~LogicalDeviceCoreSimplifier();

	LogicalDeviceCoreSimplifier& operator=(const LogicalDeviceCoreSimplifier&) noexcept = delete;

	void CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected, bool throwOnSwapchainExist, bool throwOnDeviceChange);

private:
	LogicalDeviceCoreInternal& _internal;
};