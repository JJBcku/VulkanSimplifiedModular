module RunProgram.CreateDeviceDependent;

void CreateDeviceDependent(VulkanData& data)
{
	SwapchainCreationData swapchainCreation;

	swapchainCreation.surfacePresentMode = SurfacePresentModeBits::PRESENT_MODE_FIFO_STRICT;

	auto& srgb = data.instanceDependent->surfaceSupport.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace;
	auto& blitDst = data.instanceDependent->deviceFormatsSupport.formatFeaturesOptimalImageSupport.blitDst;

	if ((srgb.secondSet & DATA_FORMAT_BGRA8_SRGB) == DATA_FORMAT_BGRA8_SRGB && (blitDst.secondSet & DATA_FORMAT_BGRA8_SRGB) == DATA_FORMAT_BGRA8_SRGB)
	{
		swapchainCreation.format.dataSet = DataFormatSetEnum::DATA_SET_TWO;
		swapchainCreation.format.dataFormat = DATA_FORMAT_BGRA8_SRGB;
	}
	else
	{
		swapchainCreation.format.dataSet = DataFormatSetEnum::DATA_SET_SEVEN;
		swapchainCreation.format.dataFormat = DATA_FORMAT_RGBA8_SRGB;
	}

	swapchainCreation.imageAmount = data.instanceDependent->surfaceSupport.minImageCount + 1;
	if (swapchainCreation.imageAmount > data.instanceDependent->surfaceSupport.maxImageCount)
		swapchainCreation.imageAmount = data.instanceDependent->surfaceSupport.maxImageCount;

	auto instance = data.basicData->main.value().GetInstanceSimplifier();
	auto deviceList = instance.GetDeviceListSimplifier();
	auto device = deviceList.GetLogicalDeviceSimplifier(data.instanceDependent->deviceID);

	device.CreateSwapchain(data.basicData->windowID, swapchainCreation, false, true, true);
}