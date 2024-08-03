module RunProgram.CreateInstanceDependent;

size_t ChooseGPU(DeviceListSimplifier& deviceList)
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

std::uint32_t PickGraphicQueueFamily(const PhysicalDeviceSimplifier& physicalDevice)
{
	std::uint32_t choosenFamily = std::numeric_limits<std::uint32_t>::max();

	auto deviceData = physicalDevice.GetVulkanPropertiesSimplified();
	auto& queueData = deviceData.queueFamilies;

	std::optional<std::uint32_t> bestNonVideoGraphicQueueFamily;
	std::uint32_t bestNonVideoGraphicQueueFamilyGranularity = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoGraphicQueueFamilyTimestamp = 0;

	std::optional<std::uint32_t> bestVideoGraphicQueueFamily;
	std::uint32_t bestVideoGraphicQueueFamilyGranularity = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoGraphicQueueFamilyTimestamp = 0;

	for (size_t i = 0; i < queueData.size(); i++)
	{
		auto& family = queueData[i];

		if ((family.queueTypes & QUEUE_TYPE_GRAPHICS) != QUEUE_TYPE_GRAPHICS)
			continue;

		bool better = false;
		auto biggestGranularity = std::max(std::max(family.minImageTransferGranularityWidth, family.minImageTransferGranularityHeight), family.minImageTransferGranularityDepth);

		if ((family.queueTypes & QUEUE_TYPE_VIDEO_DECODE) != QUEUE_TYPE_VIDEO_DECODE && (family.queueTypes & QUEUE_TYPE_VIDEO_ENCODE) != QUEUE_TYPE_VIDEO_ENCODE)
		{
			if (bestNonVideoGraphicQueueFamilyGranularity > biggestGranularity)
			{
				better = true;
			}
			else if (bestNonVideoGraphicQueueFamilyGranularity == biggestGranularity && bestNonVideoGraphicQueueFamilyTimestamp < family.timespampValidBits)
			{
				better = true;
			}

			if (better)
			{
				bestNonVideoGraphicQueueFamily = static_cast<std::uint32_t>(i);
				bestNonVideoGraphicQueueFamilyGranularity = biggestGranularity;
				bestNonVideoGraphicQueueFamilyTimestamp = family.timespampValidBits;
			}
		}
		else
		{
			if (bestVideoGraphicQueueFamilyGranularity > biggestGranularity)
			{
				better = true;
			}
			else if (bestVideoGraphicQueueFamilyGranularity == biggestGranularity && bestVideoGraphicQueueFamilyTimestamp < family.timespampValidBits)
			{
				better = true;
			}

			if (better)
			{
				bestVideoGraphicQueueFamily = static_cast<std::uint32_t>(i);
				bestVideoGraphicQueueFamilyGranularity = biggestGranularity;
				bestVideoGraphicQueueFamilyTimestamp = family.timespampValidBits;
			}
		}
	}

	if (bestNonVideoGraphicQueueFamily.has_value())
	{
		choosenFamily = bestNonVideoGraphicQueueFamily.value();
	}
	else if (bestVideoGraphicQueueFamily.has_value())
	{
		choosenFamily = bestVideoGraphicQueueFamily.value();
	}
	else
	{
		throw std::runtime_error("PickGraphicQueueFamily Error: Program failed to find a graphics queue!");
	}

	return choosenFamily;
}

std::optional<std::uint32_t> TryToFindTransferOnlyQueue(const PhysicalDeviceSimplifier& physicalDevice)
{
	std::optional<std::uint32_t> choosenFamily;

	auto deviceData = physicalDevice.GetVulkanPropertiesSimplified();
	auto& queueData = deviceData.queueFamilies;

	std::optional<std::uint32_t> bestNonVideoTransferOnlyQueueFamily;
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyGranularity = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyTimestamp = 0;

	std::optional<std::uint32_t> bestVideoTransferOnlyQueueFamily;
	std::uint32_t bestVideoTransferOnlyQueueFamilyGranularity = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoTransferOnlyQueueFamilyTimestamp = 0;

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
			if (bestNonVideoTransferOnlyQueueFamilyGranularity > biggestGranularity)
			{
				better = true;
			}
			else if (bestNonVideoTransferOnlyQueueFamilyGranularity == biggestGranularity && bestNonVideoTransferOnlyQueueFamilyTimestamp < family.timespampValidBits)
			{
				better = true;
			}

			if (better)
			{
				bestNonVideoTransferOnlyQueueFamily = static_cast<std::uint32_t>(i);
				bestNonVideoTransferOnlyQueueFamilyGranularity = biggestGranularity;
				bestNonVideoTransferOnlyQueueFamilyTimestamp = family.timespampValidBits;
			}
		}
		else
		{
			if (bestVideoTransferOnlyQueueFamilyGranularity > biggestGranularity)
			{
				better = true;
			}
			else if (bestVideoTransferOnlyQueueFamilyGranularity == biggestGranularity && bestVideoTransferOnlyQueueFamilyTimestamp < family.timespampValidBits)
			{
				better = true;
			}

			if (better)
			{
				bestVideoTransferOnlyQueueFamily = static_cast<std::uint32_t>(i);
				bestVideoTransferOnlyQueueFamilyGranularity = biggestGranularity;
				bestVideoTransferOnlyQueueFamilyTimestamp = family.timespampValidBits;
			}
		}
	}

	if (bestNonVideoTransferOnlyQueueFamily.has_value())
	{
		choosenFamily = bestNonVideoTransferOnlyQueueFamily.value();
	}
	else if (bestVideoTransferOnlyQueueFamily.has_value())
	{
		choosenFamily = bestVideoTransferOnlyQueueFamily.value();
	}

	return choosenFamily;
}

void CreateInstanceDependent(VulkanData& data)
{
	auto& main = data.basicData.get()->main.value();

	auto instance = main.GetInstanceSimplifier();

	auto deviceList = instance.GetDeviceListSimplifier();

	size_t choosenGPU = ChooseGPU(deviceList);

	auto physicalDevice = deviceList.GetPhysicalDeviceSimplifier(choosenGPU);

	data.instanceDependent = std::make_unique<VulkanDataInstanceDependent>();

	LogicalDeviceCreationInfo deviceCreationInfo;
	deviceCreationInfo.physicalGPUIndex = choosenGPU;
	deviceCreationInfo.queuesCreateInfo.reserve(2);
	deviceCreationInfo.deviceInstanceName = "Only Used Device";
	
	QueueCreateInfo graphicQueueCreateInfo;
	graphicQueueCreateInfo.queueFamily = PickGraphicQueueFamily(physicalDevice);
	deviceCreationInfo.queuesCreateInfo.push_back(graphicQueueCreateInfo);
	data.instanceDependent->graphicsQueue = 0U;

	auto transferOnly = TryToFindTransferOnlyQueue(physicalDevice);

	if (transferOnly.has_value())
	{
		QueueCreateInfo transferOnlyQueueCreateInfo;
		transferOnlyQueueCreateInfo.queueFamily = transferOnly.value();
		deviceCreationInfo.queuesCreateInfo.push_back(transferOnlyQueueCreateInfo);
		data.instanceDependent->transferQueue = 1U;
	}

	data.instanceDependent->deviceID = deviceList.AddLogicalDevice(deviceCreationInfo);
}