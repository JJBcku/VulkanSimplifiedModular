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

	swapchainCreation.imageAmount = data.instanceDependent->surfaceSupport.minImageCount + 1;
	if (swapchainCreation.imageAmount > data.instanceDependent->surfaceSupport.maxImageCount)
		swapchainCreation.imageAmount = data.instanceDependent->surfaceSupport.maxImageCount;

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

	data.deviceDependent->graphicsCommandPool = commandPoolList.AddCommandPoolWithoutIndividualReset(true, data.instanceDependent->graphicsQueue, 1, 1, 4);

	if (data.instanceDependent->transferQueue.has_value())
		data.deviceDependent->transferCommandPool = commandPoolList.AddCommandPoolWithoutIndividualReset(true, data.instanceDependent->transferQueue.value(), 1, 1, 4);

	if (data.instanceDependent->graphicsQueue != data.instanceDependent->presentQueue)
		data.deviceDependent->presentCommandPool = commandPoolList.AddCommandPoolWithoutIndividualReset(true, data.instanceDependent->presentQueue, 1, 1, 4);
}