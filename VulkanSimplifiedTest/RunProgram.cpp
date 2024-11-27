module RunProgram;

void RunProgram()
{
	MainSettings settings;

    VulkanData data;

    CreateBasics(data, settings);
    CreateInstanceDependent(data);
    CreateDeviceDependent(data);
    CreateSharedData(data);
    CreateRenderPassData(data);
    CreatePipelineLayout(data);
    CreatePipeline(data, 800U, 600U);
    CreatePipeline(data, 1200U, 900U);

    size_t frameNumber = 0;

    while (!settings.GetQuit())
    {
        HandleEvents(data);
        RunFrame(data, frameNumber);

        if (++frameNumber >= data.deviceDependent->imageAmount)
            frameNumber = 0;
    }

    auto instance = data.basicData->main.value().GetInstanceSimplifier();
    auto deviceList = instance.GetDeviceListSimplifier();
    auto deviceMain = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
    auto deviceCore = deviceMain.GetLogicalDeviceCoreSimplifier();
    deviceCore.WaitIdle();
}