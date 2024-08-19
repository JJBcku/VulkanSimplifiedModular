module RunProgram;

void RunProgram()
{
	MainSettings settings;

    VulkanData data;

    CreateBasics(data, settings);
    CreateInstanceDependent(data);
    CreateDeviceDependent(data);
    CreateSharedData(data);

    while (!settings.GetQuit())
    {
        HandleEvents(data);
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
    }
}