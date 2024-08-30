module RunProgram.CreateSharedData;

void CreateSharedData(VulkanData& data)
{
	data.sharedData = std::make_unique<VulkanSharedData>();

	auto sharedDataList = data.basicData->main.value().GetSharedDataListSimplifier();

	auto sharedPipelineData = sharedDataList.GetSharedPipelineDataSimplifier();

	data.sharedData->_pipelineVertexShaderData = sharedPipelineData.AddShaderSharedPipelineData("main", SHADER_TYPE_VERTEX);
	data.sharedData->_pipelineFragmentShaderData = sharedPipelineData.AddShaderSharedPipelineData("main", SHADER_TYPE_FRAGMENT);
	data.sharedData->_vertexInputData = sharedPipelineData.AddVertexInputSharedPipelineData({}, {});
	data.sharedData->_pipelineInputAssembly = sharedPipelineData.AddPipelineInputAssemblyData(PipelinePrimitiveTopology::TRIANGLE_LIST, false);
	data.sharedData->_pipelineRasterizationAssembly = sharedPipelineData.AddPipelineRasterizationData(PipelinePolygonMode::FILL, true, true);
	data.sharedData->_pipelineMultisampling = sharedPipelineData.AddPipelineMultisampleData(SAMPLE_1, {});

	ColorBlendingComponentFlags colorBlendingComponents = COLOR_COMPONENT_R | COLOR_COMPONENT_G | COLOR_COMPONENT_B | COLOR_COMPONENT_A;

	data.sharedData->_pipelineColorBlendAttachment = sharedPipelineData.AddPipelineColorBlendAttachment(colorBlendingComponents, ColorBlendingPreset::NO_BLENDING);
}