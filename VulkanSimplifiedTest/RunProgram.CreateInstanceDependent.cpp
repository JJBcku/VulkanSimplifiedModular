module RunProgram.CreateInstanceDependent;

static bool CheckFormatSupport(const FormatsSupportedImageFeaturesList& supportedImageFormats, const SurfaceSupportedColorspaceFormatsLists& surfaceColorspace,
	const DataFormatSetIndependentID& formatID)
{
	return CheckFormatSupport(supportedImageFormats.blitDst, formatID) && CheckFormatSupport(surfaceColorspace.srgbNonlinearColorspace, formatID);
}

static size_t ChooseGPU(DeviceListSimplifier& deviceList, IDObject<WindowPointer> windowID)
{
	size_t ret = 0;

	size_t gpuAmount = deviceList.GetPhysicalDeviceListSize();

	std::uint32_t bestDiscreteGpuApi = 0;
	std::optional<size_t> bestDiscreteGpu;

	std::uint32_t bestIntegratedGpuApi = 0;
	std::optional<size_t> bestIntegratedGpu;

	std::uint32_t bestCpuApi = 0;
	std::optional<size_t> bestCpu;

	for (size_t i = 0; i < gpuAmount; i++)
	{
		auto deviceInfo = deviceList.GetPhysicalDeviceSimplifier(i);
		auto deviceProperties = deviceInfo.GetVulkanPropertiesSimplified();

		if ((deviceProperties.deviceExtensions.khrExtensions & DEVICE_KHR_EXTENSION_SWAPCHAIN) != DEVICE_KHR_EXTENSION_SWAPCHAIN)
			continue;

		auto deviceSurfaceSupport = deviceInfo.GetSurfaceSupport(windowID);

		if ((deviceSurfaceSupport.surfaceUsageFlags & IMAGE_USAGE_TRANSFER_DST) != IMAGE_USAGE_TRANSFER_DST)
			continue;

		if ((deviceSurfaceSupport.surfacePresentModes & PRESENT_MODE_FIFO_STRICT) != PRESENT_MODE_FIFO_STRICT)
			continue;

		auto& surfaceSupport = deviceSurfaceSupport.surfaceSupportedSwapchainFormats;
		auto& imageSupport = deviceProperties.deviceFormatsSupport.formatFeaturesOptimalImageSupport;

		if (!CheckFormatSupport(imageSupport, surfaceSupport, DATA_FORMAT_BGRA8_UNORM) &&
			!CheckFormatSupport(imageSupport, surfaceSupport, DATA_FORMAT_RGBA8_UNORM))
			continue;

		if (!CheckFormatSupport(imageSupport.colorAttachment, DATA_FORMAT_BGRA8_UNORM) &&
			!CheckFormatSupport(imageSupport.colorAttachment, DATA_FORMAT_RGBA8_UNORM))
			continue;

		if (!CheckFormatSupport(deviceProperties.deviceFormatsSupport.formatFeaturesBufferSupport.vertexBuffer, DATA_FORMAT_RGBA32_SFLOAT))
			continue;

		switch (deviceProperties.deviceType)
		{
		case DeviceType::OTHER:
			break;
		case DeviceType::INTERGRATED_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestIntegratedGpuApi)
			{
				bestIntegratedGpu = i;
				bestIntegratedGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case DeviceType::DISCRETE_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestDiscreteGpuApi)
			{
				bestDiscreteGpu = i;
				bestDiscreteGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case DeviceType::VIRTUAL_GPU:
			break;
		case DeviceType::CPU:
			if (deviceProperties.apiMaxSupportedVersion > bestCpuApi)
			{
				bestCpu = i;
				bestCpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		default:
			break;
		}
	}

	if (bestDiscreteGpu.has_value())
	{
		ret = bestDiscreteGpu.value();
	}
	else if (bestIntegratedGpu.has_value())
	{
		ret = bestIntegratedGpu.value();
	}
	else if (bestCpu.has_value())
	{
		ret = bestCpu.value();
	}
	else
	{
		throw std::runtime_error("Program found no suitable device!");
	}

	return ret;
}

static std::pair<std::uint32_t, bool> PickGraphicQueueFamily(PhysicalDeviceSimplifier& physicalDevice, const std::vector<bool>& queuePresentSupport)
{
	std::pair<std::uint32_t, bool> choosenFamily = { std::numeric_limits<std::uint32_t>::max(), false};

	auto deviceData = physicalDevice.GetVulkanPropertiesSimplified();
	auto& queueData = deviceData.queueFamilies;

	if (queueData.size() != queuePresentSupport.size())
		throw std::runtime_error("PickGraphicQueueFamily Error: vector size mismatch!");

	std::optional<std::uint32_t> bestNonVideoGraphicQueueFamilyPresenting;
	std::uint32_t bestNonVideoGraphicQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoGraphicQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestNonVideoGraphicQueueFamilyNonPresenting;
	std::uint32_t bestNonVideoGraphicQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoGraphicQueueFamilyTimestampNonPresenting = 0;

	std::optional<std::uint32_t> bestVideoGraphicQueueFamilyPresenting;
	std::uint32_t bestVideoGraphicQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoGraphicQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestVideoGraphicQueueFamilyNonPresenting;
	std::uint32_t bestVideoGraphicQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoGraphicQueueFamilyTimestampNonPresenting = 0;

	for (size_t i = 0; i < queueData.size(); i++)
	{
		auto& family = queueData[i];

		if ((family.queueTypes & QUEUE_TYPE_GRAPHICS) != QUEUE_TYPE_GRAPHICS)
			continue;

		bool better = false;
		auto biggestGranularity = std::max(std::max(family.minImageTransferGranularityWidth, family.minImageTransferGranularityHeight), family.minImageTransferGranularityDepth);

		if ((family.queueTypes & QUEUE_TYPE_VIDEO_DECODE) != QUEUE_TYPE_VIDEO_DECODE && (family.queueTypes & QUEUE_TYPE_VIDEO_ENCODE) != QUEUE_TYPE_VIDEO_ENCODE)
		{
			if (queuePresentSupport[i])
			{
				if (bestNonVideoGraphicQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoGraphicQueueFamilyGranularityPresenting == biggestGranularity && bestNonVideoGraphicQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoGraphicQueueFamilyPresenting = static_cast<std::uint32_t>(i);
					bestNonVideoGraphicQueueFamilyGranularityPresenting = biggestGranularity;
					bestNonVideoGraphicQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestNonVideoGraphicQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoGraphicQueueFamilyGranularityNonPresenting == biggestGranularity && bestNonVideoGraphicQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoGraphicQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
					bestNonVideoGraphicQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestNonVideoGraphicQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
		else
		{
			if (queuePresentSupport[i])
			{
				if (bestVideoGraphicQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoGraphicQueueFamilyGranularityPresenting == biggestGranularity && bestVideoGraphicQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoGraphicQueueFamilyPresenting = static_cast<std::uint32_t>(i);
					bestVideoGraphicQueueFamilyGranularityPresenting = biggestGranularity;
					bestVideoGraphicQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestVideoGraphicQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoGraphicQueueFamilyGranularityNonPresenting == biggestGranularity && bestVideoGraphicQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoGraphicQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
					bestVideoGraphicQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestVideoGraphicQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
	}

	if (bestNonVideoGraphicQueueFamilyPresenting.has_value())
	{
		choosenFamily.first = bestNonVideoGraphicQueueFamilyPresenting.value();
		choosenFamily.second = true;
	}
	else if (bestNonVideoGraphicQueueFamilyNonPresenting.has_value())
	{
		choosenFamily.first = bestNonVideoGraphicQueueFamilyNonPresenting.value();
		choosenFamily.second = false;
	}
	else if (bestVideoGraphicQueueFamilyPresenting.has_value())
	{
		choosenFamily.first = bestVideoGraphicQueueFamilyPresenting.value();
		choosenFamily.second = true;
	}
	else if (bestVideoGraphicQueueFamilyNonPresenting.has_value())
	{
		choosenFamily.first = bestVideoGraphicQueueFamilyNonPresenting.value();
		choosenFamily.second = false;
	}
	else
	{
		throw std::runtime_error("PickGraphicQueueFamily Error: Program failed to find a graphics queue!");
	}

	return choosenFamily;
}

static std::optional<std::pair<std::uint32_t, bool>> TryToFindTransferOnlyQueue(const PhysicalDeviceSimplifier& physicalDevice, const std::vector<bool>& queuePresentSupport)
{
	std::optional<std::pair<std::uint32_t, bool>> choosenFamily;

	auto deviceData = physicalDevice.GetVulkanPropertiesSimplified();
	auto& queueData = deviceData.queueFamilies;

	std::optional<std::uint32_t> bestNonVideoTransferOnlyQueueFamilyPresenting;
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestNonVideoTransferOnlyQueueFamilyNonPresenting;
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting = 0;

	std::optional<std::uint32_t> bestVideoTransferOnlyQueueFamilyPresenting;
	std::uint32_t bestVideoTransferOnlyQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoTransferOnlyQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestVideoTransferOnlyQueueFamilyNonPresenting;
	std::uint32_t bestVideoTransferOnlyQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoTransferOnlyQueueFamilyTimestampNonPresenting = 0;

	for (size_t i = 0; i < queueData.size(); i++)
	{
		auto& family = queueData[i];

		if ((family.queueTypes & QUEUE_TYPE_GRAPHICS) == QUEUE_TYPE_GRAPHICS || (family.queueTypes & QUEUE_TYPE_COMPUTE) == QUEUE_TYPE_COMPUTE)
			continue;

		if ((family.queueTypes & QUEUE_TYPE_TRANSFER) != QUEUE_TYPE_TRANSFER)
			continue;

		bool better = false;
		auto biggestGranularity = std::max(std::max(family.minImageTransferGranularityWidth, family.minImageTransferGranularityHeight), family.minImageTransferGranularityDepth);

		if ((family.queueTypes & QUEUE_TYPE_VIDEO_DECODE) != QUEUE_TYPE_VIDEO_DECODE && (family.queueTypes & QUEUE_TYPE_VIDEO_ENCODE) != QUEUE_TYPE_VIDEO_ENCODE)
		{
			if (queuePresentSupport[i])
			{
				if (bestNonVideoTransferOnlyQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoTransferOnlyQueueFamilyGranularityPresenting == biggestGranularity && bestNonVideoTransferOnlyQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoTransferOnlyQueueFamilyPresenting = static_cast<std::uint32_t>(i);
					bestNonVideoTransferOnlyQueueFamilyGranularityPresenting = biggestGranularity;
					bestNonVideoTransferOnlyQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting == biggestGranularity && bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoTransferOnlyQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
					bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}		
		}
		else
		{
			if (queuePresentSupport[i])
			{
				if (bestVideoTransferOnlyQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoTransferOnlyQueueFamilyGranularityPresenting == biggestGranularity && bestVideoTransferOnlyQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoTransferOnlyQueueFamilyPresenting = static_cast<std::uint32_t>(i);
					bestVideoTransferOnlyQueueFamilyGranularityPresenting = biggestGranularity;
					bestVideoTransferOnlyQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestVideoTransferOnlyQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoTransferOnlyQueueFamilyGranularityNonPresenting == biggestGranularity && bestVideoTransferOnlyQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoTransferOnlyQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
					bestVideoTransferOnlyQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestVideoTransferOnlyQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
	}

	if (bestNonVideoTransferOnlyQueueFamilyPresenting.has_value())
	{
		choosenFamily = { bestNonVideoTransferOnlyQueueFamilyPresenting.value(), true };
	}
	else if (bestNonVideoTransferOnlyQueueFamilyNonPresenting.has_value())
	{
		choosenFamily = { bestNonVideoTransferOnlyQueueFamilyNonPresenting.value(), false };
	}
	else if (bestVideoTransferOnlyQueueFamilyPresenting.has_value())
	{
		choosenFamily = { bestVideoTransferOnlyQueueFamilyPresenting.value(), true };
	}
	else if (bestVideoTransferOnlyQueueFamilyNonPresenting.has_value())
	{
		choosenFamily = { bestVideoTransferOnlyQueueFamilyNonPresenting.value(), false };
	}

	return choosenFamily;
}

static std::uint32_t FindPresentingQueue(const std::vector<bool>& queuePresentSupport)
{
	std::uint32_t ret = std::numeric_limits<std::uint32_t>::max();

	for (size_t i = 0; i < queuePresentSupport.size(); i++)
	{
		if (queuePresentSupport[i])
		{
			ret = static_cast<std::uint32_t>(i);
			break;
		}
	}

	if (ret == std::numeric_limits<std::uint32_t>::max())
		throw std::runtime_error("PickGraphicQueueFamily Error: Program failed to find a present queue!");

	return ret;
}

void CreateInstanceDependent(VulkanData& data)
{
	auto& main = data.basicData.get()->main.value();

	auto instance = main.GetInstanceSimplifier();

	auto deviceList = instance.GetDeviceListSimplifier();

	size_t choosenGPU = ChooseGPU(deviceList, data.basicData->windowID);

	auto physicalDevice = deviceList.GetPhysicalDeviceSimplifier(choosenGPU);
	auto deviceProperties = physicalDevice.GetVulkanPropertiesSimplified();

	data.instanceDependent = std::make_unique<VulkanDataInstanceDependent>();

	LogicalDeviceCreationInfo deviceCreationInfo;
	deviceCreationInfo.physicalGPUIndex = choosenGPU;
	deviceCreationInfo.queuesCreateInfo.reserve(3);
	deviceCreationInfo.logicalDeviceName = "Only device used";

	deviceCreationInfo.requestedExtensions.khrExtensions = DEVICE_KHR_EXTENSION_SWAPCHAIN;

	auto surfaceSupport = physicalDevice.GetSurfaceSupport(data.basicData->windowID);
	
	QueueCreateInfo graphicQueueCreateInfo;

	auto graphicQueueData = PickGraphicQueueFamily(physicalDevice, surfaceSupport.queuePresentingSupport);
	graphicQueueCreateInfo.queueFamily = graphicQueueData.first;
	deviceCreationInfo.queuesCreateInfo.push_back(graphicQueueCreateInfo);
	data.instanceDependent->graphicsQueue = 0U;

	auto transferOnly = TryToFindTransferOnlyQueue(physicalDevice, surfaceSupport.queuePresentingSupport);

	if (transferOnly.has_value())
	{
		data.instanceDependent->transferQueue = deviceCreationInfo.queuesCreateInfo.size();
		QueueCreateInfo transferOnlyQueueCreateInfo;
		transferOnlyQueueCreateInfo.queueFamily = transferOnly.value().first;
		deviceCreationInfo.queuesCreateInfo.push_back(transferOnlyQueueCreateInfo);
	}

	if (transferOnly.has_value() && transferOnly.value().second)
	{
		data.instanceDependent->presentQueue = data.instanceDependent->transferQueue.value();
	}
	else if (graphicQueueData.second)
	{
		data.instanceDependent->presentQueue = data.instanceDependent->graphicsQueue;
	}
	else
	{
		data.instanceDependent->presentQueue = deviceCreationInfo.queuesCreateInfo.size();
		QueueCreateInfo presentOnlyQueueCreateInfo;
		presentOnlyQueueCreateInfo.queueFamily = FindPresentingQueue(surfaceSupport.queuePresentingSupport);
		deviceCreationInfo.queuesCreateInfo.push_back(presentOnlyQueueCreateInfo);
	}

	DeviceMainCreationData mainCreationData;

	mainCreationData.shaderList.initialFragmentListCapacity = 1;
	mainCreationData.shaderList.initialVertexListCapacity = 1;
	mainCreationData.commandPoolList.noIndividualResetCommandPoolListInitialReservation = 4;

	mainCreationData.imageList.framebuffersListInitialCapacity = 1;
	
	for (size_t i = 0; i < mainCreationData.memoryList.memoryInitialAllocationReservations.size(); ++i)
		mainCreationData.memoryList.memoryInitialAllocationReservations[i] = 0x4;

	data.instanceDependent->deviceID = deviceList.AddLogicalDevice(deviceCreationInfo, mainCreationData);
	data.instanceDependent->usedDeviceExtensions = deviceCreationInfo.requestedExtensions;
	data.instanceDependent->device10Limits = deviceProperties.device10Limits;
	data.instanceDependent->deviceFormatsSupport = deviceProperties.deviceFormatsSupport;
	data.instanceDependent->surfaceSupport = surfaceSupport;
}