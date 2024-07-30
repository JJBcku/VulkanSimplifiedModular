module;

module VulkanSimplifiers.Main;

MainSimplifier::MainSimplifier(const MainSimplifierInitData& initData)
{
	_internal = std::make_unique<MainInternal>(initData);
}

MainSimplifier::~MainSimplifier()
{
}

VulkanVersionData MainSimplifier::GetAppVersion() const
{
	return _internal->GetAppVersion();
}

EventHandlingSimplifier MainSimplifier::GetEventHandler()
{
	return _internal->GetEventHandler();
}

InstanceSimplifier MainSimplifier::GetInstanceSimplifier()
{
	return _internal->GetInstanceSimplifier();
}

WindowListSimplifier MainSimplifier::GetWindowListSimplifier()
{
	return _internal->GetWindowListSimplifier();
}

VulkanVersionData MainSimplifier::GetMaxAvailableVulkanVersion() const
{
	return _internal->GetMaxAvailableVulkanVersion();
}

InstanceExtensionList MainSimplifier::GetAvailableInstanceExtensions() const
{
	return _internal->GetAvailableInstanceExtensions();
}

void MainSimplifier::CreateIntance(const InstanceCreationInfo& instanceCreateInfo)
{
	_internal->CreateIntance(instanceCreateInfo);
}
