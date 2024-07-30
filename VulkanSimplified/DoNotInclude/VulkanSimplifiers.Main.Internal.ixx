module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Main.Internal;

import std;
import VulkanSimplifiers.Main.Data;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.EventHandling.Internal;
import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.Instance.Internal;

import VulkanSimplifiers.Common.VulkanVersionData;

export class MainInternal
{
public:
	explicit MainInternal(const MainSimplifierInitData& initData);
	~MainInternal();

	MainInternal(const MainInternal&) = delete;
	MainInternal& operator=(const MainInternal&) = delete;

	VulkanVersionData GetAppVersion() const;

	EventHandlingInternal& GetEventHandler();
	InstanceInternal& GetInstanceSimplifier();
	WindowListInternal& GetWindowListSimplifier();

	const EventHandlingInternal& GetEventHandler() const;
	const InstanceInternal& GetInstanceSimplifier() const;
	const WindowListInternal& GetWindowListSimplifier() const;

	VulkanVersionData GetMaxAvailableVulkanVersion() const;
	InstanceExtensionList GetAvailableInstanceExtensions() const;

private:
	std::string _appTitle;
	std::string _appVariantTitle;
	VulkanVersionData _appVersion;
	std::string _engineName;
	VulkanVersionData _engineVersion;

	VulkanVersionData _maxApiVersion;
	InstanceExtensionList _availableExtensions;

	EventHandlingInternal _eventHandler;
	InstancePointer _instance;
	WindowListInternal _windowList;

	std::uint32_t FindMaximumAvailableVulkanVersion() const;
	InstanceExtensionList CompileAvailableExtensionList(const std::vector<VkExtensionProperties>& extensions) const;

	std::vector<const char*> CompileRequestedExtensionsList();
};