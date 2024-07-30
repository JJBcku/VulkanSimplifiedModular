module RunProgram.CreateBasics;

void CreateBasics(VulkanData& data, MainSettings& settings)
{
	data.basicData = std::make_unique<VulkanDataBasic>();

	auto& basic = *data.basicData;

	MainSimplifierInitData initData;

	initData.appTitle = "Vulkan Simplified test app";
#if defined(_DEBUG) || defined(DEBUG)
	initData.appVariantTitle = "x64 Debug";
#else
	initData.appVariantTitle = "x64 Release";
#endif
	initData.appVersion.SetVulkanPatchVersion(2);
	initData.engineName = "Vulkan Simplified Test Engine";
	initData.engineVersion = initData.appVersion;

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

	auto vulkanMaxVersion = main.GetMaxAvailableVulkanVersion();
}