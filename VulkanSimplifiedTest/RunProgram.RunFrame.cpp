module RunProgram.RunFrame;

void RunFrame(VulkanData& data, size_t frameNumber)
{
	auto instance = data.basicData->main.value().GetInstanceSimplifier();
	auto deviceList = instance.GetDeviceListSimplifier();
	auto deviceMain = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
	auto deviceCommandPoolList = deviceMain.GetCommandPoolListSimplifier();
	auto deviceCommandPoolQFGraphicsList = deviceCommandPoolList.GetCommandPoolQFGroupListSimplifier(data.instanceDependent->graphicsQueue);
	auto deviceGraphicsCommandPool = deviceCommandPoolQFGraphicsList.GetCommandPoolWithIndividualResetSimplifier(data.deviceDependent->graphicsCommandPool);
	auto deviceGraphicsBuffer = deviceGraphicsCommandPool.GetPrimaryCommandBufferSimplifier(data.deviceDependent->graphicsCommandBuffers[frameNumber]);
	auto synchronizationList = deviceMain.GetSynchronizationListSimplifier();

	std::vector<CommandBufferSubmitInfo> submitInfo(1, {});

	submitInfo[0].waitSemaphores.resize(1);
	submitInfo[0].commandBufferIDs.resize(1);
	submitInfo[0].signalSemaphores.resize(1);

	CommandBufferGenericID submitedBufferID;

	synchronizationList.WaitOnFences({ data.deviceDependent->inFlightFences[frameNumber] }, false);

	synchronizationList.ResetFences({ data.deviceDependent->inFlightFences[frameNumber] });

	std::uint32_t nextFrame = 0;
	deviceGraphicsBuffer.AcquireNextImage(std::numeric_limits<std::uint64_t>::max(), data.deviceDependent->imageAvailableSemaphores[frameNumber], {},
		nextFrame, data.basicData->windowID);

	if (data.instanceDependent->graphicsQueue != data.instanceDependent->presentQueue)
	{
		auto deviceCommandPoolQFPresentList = deviceCommandPoolList.GetCommandPoolQFGroupListSimplifier(data.instanceDependent->graphicsQueue);
		auto devicePresentCommandPool = deviceCommandPoolQFPresentList.GetCommandPoolWithIndividualResetSimplifier(data.deviceDependent->graphicsCommandPool);
		auto devicePresentBuffer = devicePresentCommandPool.GetPrimaryCommandBufferSimplifier(data.deviceDependent->graphicsCommandBuffers[frameNumber]);

		devicePresentBuffer.ResetCommandBuffer(false);
		devicePresentBuffer.BeginRecording(CommandBufferUsage::ONE_USE);

		devicePresentBuffer.TransitionSwapchainImageToTrasferDestination(data.basicData->windowID, { {data.instanceDependent->presentQueue, data.instanceDependent->graphicsQueue} },
			nextFrame);

		devicePresentBuffer.EndRecording();

		submitInfo[0].waitSemaphores[0] = { data.deviceDependent->imageAvailableSemaphores[frameNumber], PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT };

		submitedBufferID.IRPrimaryID.commandPoolID = data.deviceDependent->presentCommandPool.value();
		submitedBufferID.IRPrimaryID.commandBufferID = data.deviceDependent->presentCommandBuffers[frameNumber];

		submitInfo[0].commandBufferIDs[0] = submitedBufferID;

		submitInfo[0].signalSemaphores[0] = data.deviceDependent->queueTransferFinishedSemaphores[frameNumber];

		deviceCommandPoolQFPresentList.SubmitBuffers(data.instanceDependent->presentQueue, submitInfo, {});
	}

	deviceGraphicsBuffer.ResetCommandBuffer(false);

	deviceGraphicsBuffer.BeginRecording(CommandBufferUsage::ONE_USE);

	if (data.instanceDependent->graphicsQueue == data.instanceDependent->presentQueue)
	{
		deviceGraphicsBuffer.TransitionSwapchainImageToTrasferDestination(data.basicData->windowID, {}, nextFrame);
	} 
	else
	{
		deviceGraphicsBuffer.TransitionSwapchainImageToTrasferDestination(data.basicData->windowID, { {data.instanceDependent->presentQueue, data.instanceDependent->graphicsQueue} },
			nextFrame);
	}

	deviceGraphicsBuffer.BeginRenderPass(data.renderPassData->renderPass, data.pipelinesList->attachmentData->framebuffer, 0U, 0U,
		data.pipelinesList->attachmentData->width, data.pipelinesList->attachmentData->height, data.renderPassData->clearValues);

	deviceGraphicsBuffer.BindGraphicsPipeline(data.pipelinesList->currentPipeline->pipeline);
	deviceGraphicsBuffer.Draw(3, 1, 0, 0);

	deviceGraphicsBuffer.EndRenderPass();

	deviceGraphicsBuffer.BlitToSwapchainImage(data.basicData->windowID, data.pipelinesList->attachmentData->colorAttachmentImage, 0, 0, data.pipelinesList->attachmentData->width,
		data.pipelinesList->attachmentData->height, nextFrame);

	if (data.instanceDependent->graphicsQueue == data.instanceDependent->presentQueue)
	{
		deviceGraphicsBuffer.TransitionSwapchainImageToPresent(data.basicData->windowID, {}, nextFrame);
	} 
	else
	{
		deviceGraphicsBuffer.TransitionSwapchainImageToPresent(data.basicData->windowID, { {data.instanceDependent->graphicsQueue, data.instanceDependent->presentQueue} }, nextFrame);
	}
	
	deviceGraphicsBuffer.EndRecording();

	if (data.instanceDependent->graphicsQueue == data.instanceDependent->presentQueue)
	{
		submitInfo[0].waitSemaphores[0] = { data.deviceDependent->imageAvailableSemaphores[frameNumber], PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT };
	}
	else
	{
		submitInfo[0].waitSemaphores[0] = { data.deviceDependent->queueTransferFinishedSemaphores[frameNumber], PIPELINE_STAGE_ALL_COMMANDS };
	}

	submitedBufferID.type = CommandBufferIDType::IR_PRIMARY;
	submitedBufferID.IRPrimaryID.commandPoolID = data.deviceDependent->graphicsCommandPool;
	submitedBufferID.IRPrimaryID.commandBufferID = data.deviceDependent->graphicsCommandBuffers[frameNumber];
	submitInfo[0].commandBufferIDs[0] = submitedBufferID;

	submitInfo[0].signalSemaphores[0] = data.deviceDependent->renderingFinishedSemaphores[frameNumber];

	if (data.instanceDependent->graphicsQueue == data.instanceDependent->presentQueue)
	{
		deviceCommandPoolQFGraphicsList.SubmitBuffers(data.instanceDependent->graphicsQueue, submitInfo, data.deviceDependent->inFlightFences[frameNumber]);

		deviceGraphicsCommandPool.PresentSwapchainToQueue(data.basicData->windowID, { data.deviceDependent->renderingFinishedSemaphores[frameNumber] }, nextFrame);
	}
	else
	{
		deviceCommandPoolQFGraphicsList.SubmitBuffers(data.instanceDependent->graphicsQueue, submitInfo, {});

		auto deviceCommandPoolQFPresentList = deviceCommandPoolList.GetCommandPoolQFGroupListSimplifier(data.instanceDependent->graphicsQueue);
		auto devicePresentCommandPool = deviceCommandPoolQFPresentList.GetCommandPoolWithIndividualResetSimplifier(data.deviceDependent->graphicsCommandPool);
		auto devicePresentBuffer = devicePresentCommandPool.GetPrimaryCommandBufferSimplifier(data.deviceDependent->graphicsCommandBuffers[frameNumber]);

		devicePresentBuffer.ResetCommandBuffer(false);
		devicePresentBuffer.BeginRecording(CommandBufferUsage::ONE_USE);

		devicePresentBuffer.TransitionSwapchainImageToPresent(data.basicData->windowID, { {data.instanceDependent->graphicsQueue, data.instanceDependent->presentQueue} }, nextFrame);

		devicePresentBuffer.EndRecording();

		submitInfo[0].waitSemaphores[0] = { data.deviceDependent->renderingFinishedSemaphores[frameNumber], PIPELINE_STAGE_ALL_COMMANDS};

		submitedBufferID.IRPrimaryID.commandPoolID = data.deviceDependent->presentCommandPool.value();
		submitedBufferID.IRPrimaryID.commandBufferID = data.deviceDependent->presentCommandBuffers[frameNumber];

		submitInfo[0].commandBufferIDs[0] = submitedBufferID;

		submitInfo[0].signalSemaphores[0] = data.deviceDependent->queueTransferFinishedSemaphores[frameNumber];

		deviceCommandPoolQFPresentList.SubmitBuffers(data.instanceDependent->presentQueue, submitInfo, data.deviceDependent->inFlightFences[frameNumber]);
		
		devicePresentCommandPool.PresentSwapchainToQueue(data.basicData->windowID, { data.deviceDependent->queueTransferFinishedSemaphores[frameNumber] }, nextFrame);
	}
}