module RunProgram.EventHandling;

void HandleEvents(VulkanData& data)
{
	auto& main = data.basicData->main.value();
	auto eventHandler = main.GetEventHandler();

	eventHandler.HandleEvents();
}