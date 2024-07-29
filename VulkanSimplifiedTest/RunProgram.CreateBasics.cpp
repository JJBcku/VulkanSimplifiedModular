module RunProgram.CreateBasics;

void CreateBasics(VulkanData& data, MainSettings& settings)
{
	data.basicData = std::make_unique<VulkanDataBasic>();

	auto& basic = *data.basicData;

	MainSimplifierInitData initData;

	initData.appVersion.patch = 2;
	initData.appTitle = "Vulkan Simplifier test app";

	basic.main.emplace(initData);

	auto& main = basic.main.value();

	auto eventHandler = main.GetEventHandler();
	eventHandler.RegisterQuitEventCallback(settings.QuitEventCallback, &settings, 0x10);

	WindowCreationData window;

	window.windowTitle = "Module Test Window";
	window.windowWidth = 800;
	window.windowHeight = 600;

	auto windowList = main.GetWindowListSimplifier();

	basic.windowID = windowList.CreateWindow(window);

	auto windowSimplifier = windowList.GetWindowSimplifier(basic.windowID);

	auto instanceList = main.GetInstanceListSimplifier();

	auto vulkanMaxVersion = instanceList.GetMaxAvailableVulkanVersion();
}