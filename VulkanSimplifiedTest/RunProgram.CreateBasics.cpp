module RunProgram.CreateBasics;

void CreateBasics(VulkanData& data, MainSettings& settings)
{
	data.basicData = std::make_unique<VulkanDataBasic>();

	auto& basic = *data.basicData;

	MainSimplifierInitData initData;

	initData.appName = "Vulkan Simplified test app";
#if defined(_DEBUG) || defined(DEBUG)
	initData.appVariantName = "x64 Debug";
#else
	initData.appVariantName = "x64 Release";
#endif
	initData.appVersion.SetVulkanPatchVersion(0);
	initData.appVersion.SetVulkanMinorVersion(3);
	initData.engineName = "Vulkan Simplified Test Engine";
	initData.engineVersion = initData.appVersion;

	initData.sharedDataListInitData.sharedPipelineData.initialShaderPipelineInfoCapacity = 1;
	initData.sharedDataListInitData.sharedPipelineData.initialVertexInputPipelineInfoCapacity = 1;
	initData.sharedDataListInitData.sharedPipelineData.initialPipelineInputAssemblyInfoCapacity = 1;
	initData.sharedDataListInitData.sharedPipelineData.initialPipelineRasterizationInfoCapacity = 1;
	initData.sharedDataListInitData.sharedPipelineData.initialPipelineMultisampleInfoCapacity = 1;
	initData.sharedDataListInitData.sharedPipelineData.initialPipelineColorBlendAttachmentInfoCapacity = 1;

	basic.main.emplace(initData);

	auto& main = basic.main.value();

	auto eventHandler = main.GetEventHandler();
	eventHandler.RegisterQuitEventCallback(settings.QuitEventCallback, &settings, 0);

	WindowCreationData window;

	window.windowTitle = "Module Test Window";
	window.windowWidth = 800;
	window.windowHeight = 600;
	window.properties = WindowProperties::RESIZABLE;

	auto windowList = main.GetWindowListSimplifier();

	basic.windowID = windowList.CreateWindow(window);

	auto windowSimplifier = windowList.GetWindowSimplifier(basic.windowID);

	InstanceCreationInfo instanceInit;
	instanceInit.usedVulkanApiVersion = main.GetMaxAvailableVulkanVersion();
	instanceInit.windowExampleID = basic.windowID;
	instanceInit.logicalDeviceListInitialCapacity = 1;

	main.CreateIntance(instanceInit);
}