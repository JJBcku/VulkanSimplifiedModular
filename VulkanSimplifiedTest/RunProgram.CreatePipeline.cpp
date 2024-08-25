module RunProgram.CreatePipeline;

void CreatePipeline(VulkanData& data)
{
	const auto windowList = data.basicData->main->GetWindowListSimplifier();
	const auto window = windowList.GetWindowSimplifier(data.basicData->windowID);

	std::uint32_t width = 800;
	std::uint32_t heigth = 600;
}