module RunProgram.CreateSharedData;

void CreateSharedData(VulkanData& data)
{
	data.sharedData = std::make_unique<VulkanSharedData>();

	auto sharedDataList = data.basicData->main.value().GetSharedDataListSimplifier();

	auto sharedPipelineData = sharedDataList.GetSharedPipelineDataSimplifier();

	data.sharedData->_pipelineSharedData = sharedPipelineData.AddShaderSharedPipelineData("main", {});
}