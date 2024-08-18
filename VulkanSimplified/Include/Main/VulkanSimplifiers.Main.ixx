export module VulkanSimplifiers.Main;

import std;
import VulkanSimplifiers.Main.Data;
import ListTemplates.IDObject;

import VulkanSimplifiers.EventHandling;
import VulkanSimplifiers.Main.Internal;
import VulkanSimplifiers.WindowList;
import VulkanSimplifiers.Instance;

import VulkanSimplifiers.SharedDataList;
import VulkanSimplifiers.SharedDataList.Internal;

export class MainSimplifier
{
public:
	explicit MainSimplifier(const MainSimplifierInitData& initData);
	~MainSimplifier();

	MainSimplifier(const MainSimplifier&) = delete;
	MainSimplifier& operator=(const MainSimplifier&) = delete;

	VulkanVersionData GetAppVersion() const;

	EventHandlingSimplifier GetEventHandler();
	InstanceSimplifier GetInstanceSimplifier();
	WindowListSimplifier GetWindowListSimplifier();
	SharedDataListSimplifier GetSharedDataListSimplifier();

	VulkanVersionData GetMaxAvailableVulkanVersion() const;
	InstanceExtensionList GetAvailableInstanceExtensions() const;

	void CreateIntance(const InstanceCreationInfo& instanceCreateInfo);

private:
	std::unique_ptr<MainInternal> _internal;
};