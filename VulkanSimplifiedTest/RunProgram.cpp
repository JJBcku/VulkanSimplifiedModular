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

    while (!settings.IsClosingRequested())
    {
        HandleEvents(data);

        auto windowList = data.basicData->main.value().GetWindowListSimplifier();
        auto window = windowList.GetWindowSimplifier(data.basicData->windowID);

        if (window.IsPaused())
        {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(10));
        }
        else
        {
            RunFrame(data, frameNumber);

            if (++frameNumber >= data.deviceDependent->imageAmount)
                frameNumber = 0;
        }
    }

    auto instance = data.basicData->main.value().GetInstanceSimplifier();
    auto deviceList = instance.GetDeviceListSimplifier();
    auto deviceMain = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
    auto deviceCore = deviceMain.GetLogicalDeviceCoreSimplifier();
    deviceCore.WaitIdle();
}