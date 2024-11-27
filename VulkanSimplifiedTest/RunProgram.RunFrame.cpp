module RunProgram.RunFrame;

void RunFrame(VulkanData& data, size_t frameNumber)
{
	auto instance = data.basicData->main.value().GetInstanceSimplifier();
	auto deviceList = instance.GetDeviceListSimplifier();
	auto deviceMain = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
	auto deviceCommandPoolList = deviceMain.GetCommandPoolListSimplifier();
	auto deviceGraphicsCommandPool = deviceCommandPoolList.GetCommandPoolWithIndividualResetSimplifier(data.deviceDependent->graphicsCommandPool);
	auto deviceGraphicsBuffer = deviceGraphicsCommandPool.GetPrimaryCommandBufferSimplifier(data.deviceDependent->graphicsCommandBuffers[frameNumber]);
	auto synchronizationList = deviceMain.GetSynchronizationListSimplifier();

	synchronizationList.WaitOnFences({ data.deviceDependent->inFlightFences[frameNumber] }, false);

	synchronizationList.ResetFences({ data.deviceDependent->inFlightFences[frameNumber] });

	std::uint32_t nextFrame = 0;
	deviceGraphicsBuffer.AcquireNextImage(std::numeric_limits<std::uint64_t>::max(), data.deviceDependent->imageAvailableSemaphores[frameNumber], {},
		nextFrame, data.basicData->windowID);

	deviceGraphicsBuffer.ResetCommandBuffer(false);

	deviceGraphicsBuffer.BeginRecording(CommandBufferUsage::ONE_USE);

	deviceGraphicsBuffer.TransitionSwapchainImageToTrasferDestination(data.basicData->windowID, {}, nextFrame);

	deviceGraphicsBuffer.BeginRenderPass(data.renderPassData->renderPass, data.pipelinesList->attachmentData->framebuffer, 0U, 0U,
		data.pipelinesList->attachmentData->width, data.pipelinesList->attachmentData->height, data.renderPassData->clearValues);

	deviceGraphicsBuffer.BindGraphicsPipeline(data.pipelinesList->currentPipeline->pipeline);
	deviceGraphicsBuffer.Draw(3, 1, 0, 0);

	deviceGraphicsBuffer.EndRenderPass();

	deviceGraphicsBuffer.BlitToSwapchainImage(data.basicData->windowID, data.pipelinesList->attachmentData->colorAttachmentImage, 0, 0, data.pipelinesList->attachmentData->width,
		data.pipelinesList->attachmentData->height, nextFrame);

	deviceGraphicsBuffer.TransitionSwapchainImageToPresent(data.basicData->windowID, {}, nextFrame);
	
	deviceGraphicsBuffer.EndRecording();

	std::vector<CommandBufferSubmitInfo> submitInfo(1, {});

	submitInfo[0].waitSemaphores.push_back({data.deviceDependent->imageAvailableSemaphores[frameNumber], PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT });

	CommandBufferGenericID submitedBufferID;
	submitedBufferID.type = CommandBufferIDType::IR_PRIMARY;
	submitedBufferID.IRPrimaryID.commandPoolID = data.deviceDependent->graphicsCommandPool;
	submitedBufferID.IRPrimaryID.commandBufferID = data.deviceDependent->graphicsCommandBuffers[frameNumber];
	submitInfo[0].commandBufferIDs.push_back(submitedBufferID);

	submitInfo[0].signalSemaphores.push_back(data.deviceDependent->renderingFinishedSemaphores[frameNumber]);

	deviceCommandPoolList.SubmitBuffers(data.instanceDependent->graphicsQueue, submitInfo, data.deviceDependent->inFlightFences[frameNumber]);

	deviceGraphicsCommandPool.PresentSwapchainToQueue(data.basicData->windowID, { data.deviceDependent->renderingFinishedSemaphores[frameNumber] }, nextFrame);

	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
}