module RunProgram.CreateDeviceDependent;

std::vector<char> LoadShader(std::string filename)
{
	std::vector<char> ret;

	std::ifstream file;
	file.open(filename, std::ios_base::binary | std::ios_base::in | std::ios_base::ate);

	if (!file.is_open())
		throw std::runtime_error("LoadShader Error: Program failed to open the file " + filename);

	std::streampos size = file.tellg();

	ret.resize(static_cast<size_t>(size));

	file.seekg(0, std::ios_base::_Seekbeg);

	file.read(ret.data(), size);

	if (!file.good())
		throw std::runtime_error("LoadShader Error: Program failed to read the file " + filename);

	file.close();

	return ret;
}

void CreateDeviceDependent(VulkanData& data)
{
	data.deviceDependent = std::make_unique<VulkanDataDeviceDependent>();

	SwapchainCreationData swapchainCreation;

	swapchainCreation.surfacePresentMode = SurfacePresentModeBits::PRESENT_MODE_FIFO_STRICT;

	auto& srgb = data.instanceDependent->surfaceSupport.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace;
	auto& blitDst = data.instanceDependent->deviceFormatsSupport.formatFeaturesOptimalImageSupport.blitDst;

	DataFormatSetIndependentID checkID(DATA_FORMAT_BGRA8_UNORM);

	if (CheckFormatSupport(srgb, checkID) && CheckFormatSupport(blitDst, checkID))
	{
		swapchainCreation.format = checkID;
	}
	else
	{
		swapchainCreation.format = DataFormatSetIndependentID(DATA_FORMAT_RGBA8_UNORM);
	}

	data.deviceDependent->surfaceFormat = swapchainCreation.format;

	swapchainCreation.imageAmount = data.instanceDependent->surfaceSupport.maxImageCount;

	data.deviceDependent->imageAmount = swapchainCreation.imageAmount;

	auto instance = data.basicData->main.value().GetInstanceSimplifier();
	auto deviceList = instance.GetDeviceListSimplifier();
	auto deviceMain = deviceList.GetLogicalDeviceMainSimplifier(data.instanceDependent->deviceID);
	auto device = deviceMain.GetLogicalDeviceCoreSimplifier();

	device.CreateSwapchain(data.basicData->windowID, swapchainCreation, false, true, true);

	std::string shaderFolder = "shader\\";

	std::string fragmentName = "basicFragmentShader";
	std::string vertexName = "basicVertexShader";

	std::string debugExt = ".debug";
	std::string fragmentExt = ".frag";
	std::string vertexExt = ".vert";
	std::string fileExt = ".spv";

	std::string fragmentFullName = shaderFolder + fragmentName;
	std::string vertexFullName = shaderFolder + vertexName;

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	fragmentFullName += debugExt;
	vertexFullName += debugExt;
#endif

	fragmentFullName += fragmentExt + fileExt;
	vertexFullName += vertexExt + fileExt;

	auto fragmentData = LoadShader(fragmentFullName);
	auto vertexData = LoadShader(vertexFullName);

	auto shaderList = deviceMain.GetShaderListSimplifier();

	data.deviceDependent->fragmentShader = shaderList.AddFragmentShader(fragmentData);
	data.deviceDependent->vertexShader = shaderList.AddVertexShader(vertexData);

	auto commandPoolList = deviceMain.GetCommandPoolListSimplifier();
	auto commandPoolQFGraphics = commandPoolList.GetCommandPoolQFGroupListSimplifier(data.instanceDependent->graphicsQueue);

	data.deviceDependent->graphicsCommandPool = commandPoolQFGraphics.AddCommandPoolWithIndividualReset(true, data.instanceDependent->graphicsQueue, swapchainCreation.imageAmount, 0, 4);
	auto graphicsPool = commandPoolQFGraphics.GetCommandPoolWithIndividualResetSimplifier(data.deviceDependent->graphicsCommandPool);
	data.deviceDependent->graphicsCommandBuffers = graphicsPool.AllocatePrimaryCommandBuffers(swapchainCreation.imageAmount);

	if (data.instanceDependent->transferQueue.has_value())
	{
		auto commandPoolQFTransfer = commandPoolList.GetCommandPoolQFGroupListSimplifier(data.instanceDependent->transferQueue.value());

		data.deviceDependent->transferCommandPool = commandPoolQFTransfer.AddCommandPoolWithIndividualReset(true, data.instanceDependent->transferQueue.value(), swapchainCreation.imageAmount, 0, 4);
		auto transferPool = commandPoolQFTransfer.GetCommandPoolWithIndividualResetSimplifier(data.deviceDependent->transferCommandPool.value());
		data.deviceDependent->transferCommandBuffers = graphicsPool.AllocatePrimaryCommandBuffers(swapchainCreation.imageAmount);
	}

	if (data.instanceDependent->graphicsQueue != data.instanceDependent->presentQueue)
	{
		auto commandPoolQFPresent = commandPoolList.GetCommandPoolQFGroupListSimplifier(data.instanceDependent->presentQueue);

		data.deviceDependent->presentCommandPool = commandPoolQFPresent.AddCommandPoolWithIndividualReset(true, data.instanceDependent->presentQueue, swapchainCreation.imageAmount, 0, 4);
		auto presentPool = commandPoolQFPresent.GetCommandPoolWithIndividualResetSimplifier(data.deviceDependent->presentCommandPool.value());
		data.deviceDependent->presentCommandBuffers = graphicsPool.AllocatePrimaryCommandBuffers(swapchainCreation.imageAmount);
	}

	auto synchronizationList = deviceMain.GetSynchronizationListSimplifier();

	data.deviceDependent->inFlightFences.reserve(swapchainCreation.imageAmount);
	data.deviceDependent->imageAvailableSemaphores.reserve(swapchainCreation.imageAmount);
	data.deviceDependent->renderingFinishedSemaphores.reserve(swapchainCreation.imageAmount);
	data.deviceDependent->queueTransferFinishedSemaphores.reserve(swapchainCreation.imageAmount);

	for (std::uint32_t i = 0; i < swapchainCreation.imageAmount; ++i)
	{
		data.deviceDependent->inFlightFences.push_back(synchronizationList.AddFence());
		data.deviceDependent->imageAvailableSemaphores.push_back(synchronizationList.AddSemaphore());
		data.deviceDependent->renderingFinishedSemaphores.push_back(synchronizationList.AddSemaphore());
		data.deviceDependent->queueTransferFinishedSemaphores.push_back(synchronizationList.AddSemaphore());
	}
}