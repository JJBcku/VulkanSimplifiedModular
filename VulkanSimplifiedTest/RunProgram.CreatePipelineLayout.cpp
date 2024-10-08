module RunProgram.CreatePipelineLayout;

void CreatePipelineLayout(VulkanData& data)
{
	auto instance = data.basicData->main->GetInstanceSimplifier();
	auto deviceList = instance.GetDeviceListSimplifier();
	auto deviceMain = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
	auto devicePipelineDataList = deviceMain.GetDevicePipelineDataSimplifier();

	data.pipelineLayoutData = std::make_unique<VulkanPipelineLayoutData>();

	PipelineLayoutCreationData layoutCreationData;
	data.pipelineLayoutData->pipelineLayout = devicePipelineDataList.AddPipelineLayout(layoutCreationData);
}