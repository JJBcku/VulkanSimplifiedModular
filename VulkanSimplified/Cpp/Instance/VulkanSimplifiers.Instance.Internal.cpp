module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.Instance.Internal;

InstanceInternal::InstanceInternal(const InstanceInitInfo& initInfo, WindowListInternal& windowList, const SharedDataListInternal& sharedDataList)
{
	_instance = VK_NULL_HANDLE;
	_debugMessenger = VK_NULL_HANDLE;

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = initInfo.appName.c_str();
	appInfo.applicationVersion = initInfo.appVersion;
	appInfo.pEngineName = initInfo.engineName.c_str();
	appInfo.engineVersion = initInfo.engineVersion;
	appInfo.apiVersion = initInfo.usedVulkanApiVersion;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = static_cast<std::uint32_t>(initInfo.requestedLayers.size());
	createInfo.ppEnabledLayerNames = initInfo.requestedLayers.data();
	createInfo.enabledExtensionCount = static_cast<std::uint32_t>(initInfo.requestedExtensions.size());
	createInfo.ppEnabledExtensionNames = initInfo.requestedExtensions.data();

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	VkDebugUtilsMessengerCreateInfoEXT debugInfo{};
	debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	debugInfo.pfnUserCallback = debugCallback;
	debugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
	debugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;
	debugInfo.flags = 0;
	debugInfo.pNext = nullptr;
	debugInfo.pUserData = nullptr;

	createInfo.pNext = &debugInfo;
#endif

	if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
	{
		throw std::runtime_error("Error: Program failed to create vulkan instance!");
	}

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
#pragma warning(push)
#pragma warning(disable : 4191)
	auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT"));
#pragma warning(pop)

	if (func == nullptr || func(_instance, &debugInfo, nullptr, &_debugMessenger) != VK_SUCCESS)
	{
		throw std::runtime_error("Error: Program failed to create a debug messenger!");
	}
#endif

	_deviceList.emplace(_instance, initInfo.logicalDeviceListInitialCapacity, initInfo.usedVulkanApiVersion, windowList, sharedDataList);

	_deviceList.value().EnumeratePhysicalDevices();
}

InstanceInternal::~InstanceInternal()
{
	_deviceList.reset();

	if (_debugMessenger != VK_NULL_HANDLE)
	{
#pragma warning(push)
#pragma warning(disable : 4191)
		auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT"));
#pragma warning(pop)

		if (func != nullptr)
			func(_instance, _debugMessenger, nullptr);
	}

	if (_instance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(_instance, nullptr);
	}
}

VkInstance InstanceInternal::GetInstance() const
{
	return _instance;
}

DeviceListInternal& InstanceInternal::GetDeviceListSimplifier()
{
	if (!_deviceList.has_value())
		throw std::runtime_error("InstanceInternal::GetDeviceListSimplifier Error: Program tried to get an non-existent device list!");

	return _deviceList.value();
}

const DeviceListInternal& InstanceInternal::GetDeviceListSimplifier() const
{
	if (!_deviceList.has_value())
		throw std::runtime_error("InstanceInternal::GetDeviceListSimplifier const Error: Program tried to get an non-existent device list!");

	return _deviceList.value();
}
