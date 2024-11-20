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

    while (!settings.GetQuit())
    {
        HandleEvents(data);
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
    }
}