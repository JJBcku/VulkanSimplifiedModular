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

void CreateInstanceDependent(VulkanData& data)
{
	auto& main = data.basicData.get()->main.value();

	auto instance = main.GetInstanceSimplifier();

	auto deviceList = instance.GetDeviceListSimplifier();

	size_t choosenGPU = ChooseGPU(deviceList);
}