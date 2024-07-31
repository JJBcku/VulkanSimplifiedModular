module RunProgram.CreateInstanceDependent;

void CreateInstanceDependent(VulkanData& data)
{
	auto& main = data.basicData.get()->main.value();

	auto instance = main.GetInstanceSimplifier();

	auto deviceList = instance.GetDeviceListSimplifier();

	size_t physicalDeviceAmount = deviceList.GetPhysicalDeviceListSize();
}