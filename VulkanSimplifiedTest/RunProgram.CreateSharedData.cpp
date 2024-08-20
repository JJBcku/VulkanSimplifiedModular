module RunProgram.CreateSharedData;

void CreateSharedData(VulkanData& data)
{
	data.sharedData = std::make_unique<VulkanSharedData>();

	auto sharedDataList = data.basicData->main.value().GetSharedDataListSimplifier();

	auto sharedPipelineData = sharedDataList.GetSharedPipelineDataSimplifier();

	data.sharedData->_pipelineShaderData = sharedPipelineData.AddShaderSharedPipelineData("main", {});
	data.sharedData->_vertexInputData = sharedPipelineData.AddVertexInputSharedPipelineData({}, {});
	data.sharedData->_pipelineInputAssembly = sharedPipelineData.AddPipelineInputAssemblyData(PipelinePrimitiveTopology::TRIANGLE_LIST, false);
	data.sharedData->_pipelineRasterizationAssembly = sharedPipelineData.AddPipelineRasterizationData(PipelinePolygonMode::FILL, true, true);
}