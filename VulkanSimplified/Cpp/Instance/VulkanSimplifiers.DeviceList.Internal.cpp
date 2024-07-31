module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DeviceList.Internal;

DeviceListInternal::DeviceListInternal(VkInstance instance, size_t logicalDeviceListInitialCapacity) : _instance(instance), _logicalDeviceList(logicalDeviceListInitialCapacity)
{
}

DeviceListInternal::~DeviceListInternal()
{
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
			_physicalDeviceList.emplace_back(device);
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