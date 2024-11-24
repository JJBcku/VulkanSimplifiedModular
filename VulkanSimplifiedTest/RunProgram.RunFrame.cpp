module RunProgram.RunFrame;

void RunFrame(VulkanData& data, size_t frameNumber)
{
	auto instance = data.basicData->main.value().GetInstanceSimplifier();
	auto deviceList = instance.GetDeviceListSimplifier();
	auto deviceMain = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
	auto deviceCommandPoolList = deviceMain.GetCommandPoolListSimplifier();
	auto deviceGraphicsCommandPool = deviceCommandPoolList.GetCommandPoolWithoutIndividualResetSimplifier(data.deviceDependent->graphicsCommandPool);
	auto deviceGraphicsBuffer = deviceGraphicsCommandPool.GetPrimaryCommandBufferSimplifier(data.deviceDependent->graphicsCommandBuffers[frameNumber]);

	//deviceGraphicsBuffer.BeginRecording(CommandBufferUsage::ONE_USE);
	
	//deviceGraphicsBuffer.EndRecording();

	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
}