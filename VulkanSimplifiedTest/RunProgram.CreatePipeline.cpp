module RunProgram.CreatePipeline;

void CreatePipeline(VulkanData& data)
{
	std::uint32_t width = 800;
	std::uint32_t heigth = 600;

	if (!(data.pipelinesList))
		data.pipelinesList = std::make_unique<VulkanDataPipelinesList>();

	auto sharedDataList = data.basicData->main->GetSharedDataListSimplifier();
	auto pipelineSharedData = sharedDataList.GetSharedPipelineDataSimplifier();

	VulkanPipelineData add;
	add.pipelineViewport = pipelineSharedData.AddPipelineViewportData(0, 0, width, heigth, 0.0f, 1.0f);

	add.pipelineScissor = pipelineSharedData.AddPipelineScissorData(0, 0, width, heigth);
}