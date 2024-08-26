module RunProgram.CreatePipeline;

void CreatePipeline(VulkanData& data, std::uint32_t width, std::uint32_t height)
{

	if (!(data.pipelinesList))
	{
		data.pipelinesList = std::make_unique<VulkanDataPipelinesList>();
		data.pipelinesList->pipelines.reserve(4);
	}

	auto& pipelines = data.pipelinesList->pipelines;
	auto& currentPipeline = data.pipelinesList->currentPipeline;

	auto sharedDataList = data.basicData->main->GetSharedDataListSimplifier();
	auto pipelineSharedData = sharedDataList.GetSharedPipelineDataSimplifier();

	VulkanPipelineData add;
	add.pipelineViewport = pipelineSharedData.AddPipelineViewportData(0, 0, width, height, 0.0f, 1.0f);

	auto it = std::find(pipelines.cbegin(), pipelines.cend(), add.pipelineViewport);

	if (it != pipelines.cend())
	{
		currentPipeline = *it;
	}
	else
	{
		add.pipelineScissor = pipelineSharedData.AddPipelineScissorData(0, 0, width, height);

		if (pipelines.size() == pipelines.capacity())
			pipelines.reserve(pipelines.capacity() << 1);

		pipelines.push_back(add);
		currentPipeline = add;
	}
}