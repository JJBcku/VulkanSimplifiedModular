module RunProgram;

void RunProgram()
{
	MainSettings settings;

    VulkanData data;

    CreateBasics(data, settings);

    while (!settings.GetQuit())
    {
        HandleEvents(data);
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
    }
}