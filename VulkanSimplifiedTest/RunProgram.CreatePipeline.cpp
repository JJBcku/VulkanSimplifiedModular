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
	auto& attachments = data.pipelinesList->attachmentData;

	auto sharedDataList = data.basicData->main->GetSharedDataListSimplifier();
	auto pipelineSharedData = sharedDataList.GetSharedPipelineDataSimplifier();

	auto instance = data.basicData->main->GetInstanceSimplifier();
	auto deviceList = instance.GetDeviceListSimplifier();
	auto device = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
	auto devicePipelineList = device.GetDevicePipelineDataSimplifier();
	auto deviceImageList = device.GetImageDataListSimplifier();
	auto memoryList = device.GetMemoryObjectsListSimplifier();

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

		GraphicPipelineCreationData creationData;

		creationData.shaderStages.reserve(2);
		ShaderStageData stageData;

		stageData.sharedData = data.sharedData->_pipelineFragmentShaderData;
		stageData.shaderDeviceID.type = SHADER_TYPE_FRAGMENT;
		stageData.shaderDeviceID.fragmentShader.fragmentShaderID = data.deviceDependent->fragmentShader;
		creationData.shaderStages.push_back(stageData);

		stageData.sharedData = data.sharedData->_pipelineVertexShaderData;
		stageData.shaderDeviceID.type = SHADER_TYPE_VERTEX;
		stageData.shaderDeviceID.vertexShader.vertexShaderID = data.deviceDependent->vertexShader;
		creationData.shaderStages.push_back(stageData);

		creationData.vertexInputData = data.sharedData->_vertexInputData;
		creationData.inputAssemblyData = data.sharedData->_pipelineInputAssembly;

		ViewportStatePipelineDataPoint viewportData;
		viewportData.viewport = add.pipelineViewport;
		viewportData.scissor = add.pipelineScissor;
		creationData.viewportData.push_back(viewportData);

		creationData.rasterizationData = data.sharedData->_pipelineRasterizationAssembly;
		creationData.samplingData = data.sharedData->_pipelineMultisampling;
		creationData.colorBlendingData.push_back(data.sharedData->_pipelineColorBlendAttachment);

		creationData.pipelineLayout = data.pipelineLayoutData->pipelineLayout;
		creationData.renderPass = data.renderPassData->renderPass;
		creationData.subpassIndex = 0;
		creationData.pipelineDerrivationData.settings = PipelineDerrivationSettings::DO_NOT_DERRIVE;

		auto pipelineID = devicePipelineList.AddGraphicPipelines({ creationData });
		add.pipeline = pipelineID[0];

		pipelines.push_back(add);
		currentPipeline = add;
	}

	if (!attachments.has_value() || attachments.value().width != width || attachments.value().height != height)
	{
		if (attachments.has_value())
		{
			deviceImageList.RemoveSingleSampled2DImage(attachments.value().colorAttachmentImage, true);
			memoryList.FreeMemory(attachments.value().imageMemory, true);
		}
		else
		{
			attachments.emplace();
		}

		auto& attachmentData = attachments.value();

		ImageUsageFlags usageFlags = ImageUsageFlagBits::IMAGE_USAGE_COLOR_ATTACHMENT || ImageUsageFlagBits::IMAGE_USAGE_TRANSFER_SRC;

		attachmentData.colorAttachmentImage = deviceImageList.AddSingleSampled2DImage(width, height, data.deviceDependent->surfaceFormat, usageFlags, {}, false);
		attachmentData.width = width;
		attachmentData.height = height;

		size_t allocationSize = deviceImageList.GetImageSize(attachmentData.colorAttachmentImage);
		allocationSize *= 4;

		std::uint32_t memoryTypeMask = deviceImageList.GetImageMemoryTypeMask(attachmentData.colorAttachmentImage);

		std::vector<MemoryTypeProperties> acceptableMemoryTypes;
		acceptableMemoryTypes.reserve(1);
		acceptableMemoryTypes.push_back(DEVICE_LOCAL);

		attachmentData.imageMemory = memoryList.AllocateMemory(allocationSize, 4, acceptableMemoryTypes, memoryTypeMask);
		deviceImageList.BindImage(attachmentData.colorAttachmentImage, attachmentData.imageMemory);
	}
}