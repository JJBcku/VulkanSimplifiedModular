module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DeviceList.Internal;

DeviceListInternal::DeviceListInternal(VkInstance instance, size_t logicalDeviceListInitialCapacity, std::uint32_t instanceVulkanVersion,
	WindowListInternal& windowList, const SharedDataListInternal& sharedDataList) : _instance(instance), _logicalDeviceList(logicalDeviceListInitialCapacity),
	_instanceVulkanVersion(instanceVulkanVersion), _windowList(windowList), _sharedDataList(sharedDataList)
{
}

DeviceListInternal::~DeviceListInternal()
{
	_logicalDeviceList.Reset(0);
	_physicalDeviceList.clear();
}

void DeviceListInternal::EnumeratePhysicalDevices()
{
	_physicalDeviceList.clear();

	std::uint32_t size = 0;
	std::vector<VkPhysicalDevice> physicalDevices;

	vkEnumeratePhysicalDevices(_instance, &size, nullptr);

	if (size > 0)
	{
		physicalDevices.resize(size);
		_physicalDeviceList.reserve(size);

		vkEnumeratePhysicalDevices(_instance, &size, physicalDevices.data());

		for (auto& device : physicalDevices)
		{
			_physicalDeviceList.emplace_back(device, _instanceVulkanVersion, _windowList);
		}
	}
	else
	{
		throw std::runtime_error("DeviceListInternal::EnumeratePhysicalDevices Error: Program failed to find any Vulkan compatible devices!");
	}
}

size_t DeviceListInternal::GetPhysicalDeviceListSize() const
{
	return _physicalDeviceList.size();
}

PhysicalDeviceInternal& DeviceListInternal::GetPhysicalDeviceSimplifier(size_t deviceIndex)
{
	if (deviceIndex >= _physicalDeviceList.size())
		throw std::runtime_error("DeviceListInternal::GetPhysicalDeviceSimplifier Error: Program tried to get a non-existent physical device data!");

	return _physicalDeviceList[deviceIndex];
}

LogicalDeviceMainInternal& DeviceListInternal::GetLogicalDeviceMainSimplifier(IDObject<LogicalDevicePointer> deviceID)
{
	return *_logicalDeviceList.GetObject(deviceID);
}

const PhysicalDeviceInternal& DeviceListInternal::GetPhysicalDeviceSimplifier(size_t deviceIndex) const
{
	if (deviceIndex >= _physicalDeviceList.size())
		throw std::runtime_error("DeviceListInternal::GetPhysicalDeviceSimplifier const Error: Program tried to get a non-existent physical device data!");

	return _physicalDeviceList[deviceIndex];
}

const LogicalDeviceMainInternal& DeviceListInternal::GetLogicalDeviceMainSimplifier(IDObject<LogicalDevicePointer> deviceID) const
{
	return *_logicalDeviceList.GetConstObject(deviceID);
}

IDObject<LogicalDevicePointer> DeviceListInternal::AddLogicalDevice(const LogicalDeviceCreationInfo& createInfo, const DeviceMainCreationData& mainCreationData, size_t addOnReserve)
{
	auto& physicalDevice = GetPhysicalDeviceSimplifier(createInfo.physicalGPUIndex);

	auto physicalDeviceData = physicalDevice.GetVulkanPropertiesSimplified();

	LogicalDeviceInitData initData;
	initData.creationInfo = createInfo;
	initData.apiVersion = std::min(_instanceVulkanVersion, physicalDeviceData.apiMaxSupportedVersion);
	initData.physicalDevice = physicalDevice.GetPhysicalDevice();
	initData.physicalDeviceName = physicalDeviceData.deviceName;

	return _logicalDeviceList.AddObject(std::make_unique<LogicalDeviceMainInternal>(initData, physicalDevice, mainCreationData, _windowList, _sharedDataList), addOnReserve);
}
