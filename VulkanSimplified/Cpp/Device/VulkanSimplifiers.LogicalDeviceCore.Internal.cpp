module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.LogicalDeviceCore.Internal;

LogicalDeviceInitData::LogicalDeviceInitData()
{
	physicalDevice = VK_NULL_HANDLE;

	apiVersion = 0;
	padding = 0;
}

LogicalDeviceCoreInternal::LogicalDeviceCoreInternal(const LogicalDeviceInitData& initData, WindowListInternal& windowList) : _windowList(windowList)
{
	_logicalDevice = VK_NULL_HANDLE;
	_physicalDevice = initData.physicalDevice;

	_physicalDeviceName = initData.physicalDeviceName;
	_logicalDeviceName = initData.creationInfo.logicalDeviceName;
	_apiVersion = initData.apiVersion;
	_padding = 0;

	auto& queuesCreateData = initData.creationInfo.queuesCreateInfo;

	if (queuesCreateData.empty())
		throw std::runtime_error("LogicalDeviceCoreInternal Contructor Error: Program tried to create a device with no queues!");

	std::vector<std::uint32_t> uniqueQueueFamilies;
	std::vector<std::uint32_t> familiesQueueCount;
	uniqueQueueFamilies.reserve(queuesCreateData.size());
	familiesQueueCount.reserve(queuesCreateData.size());

	for (size_t i = 0; i < queuesCreateData.size(); i++)
	{
		bool found = false;
		std::uint32_t queueFamily = queuesCreateData[i].queueFamily;

		for (size_t j = 0; j < uniqueQueueFamilies.size(); j++)
		{
			if (queueFamily == uniqueQueueFamilies[j])
			{
				found = true;
				familiesQueueCount[j]++;
				break;
			}
		}

		if (!found)
		{
			uniqueQueueFamilies.push_back(queueFamily);
			familiesQueueCount.push_back(1);
		}
	}

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfo;
	std::vector<std::vector<float>> queuesPriorities;

	queueCreateInfo.reserve(uniqueQueueFamilies.size());
	queuesPriorities.resize(uniqueQueueFamilies.size());

	for (size_t i = 0; i < uniqueQueueFamilies.size(); i++)
	{
		queuesPriorities[i].reserve(uniqueQueueFamilies[i]);

		for (size_t j = 0; j < queuesCreateData.size(); j++)
		{
			std::uint32_t queueFamily = queuesCreateData[j].queueFamily;

			if (queueFamily == uniqueQueueFamilies[i])
			{
				queuesPriorities[i].push_back(queuesCreateData[j].queuePriority);
			}
		}

		if (static_cast<std::uint32_t>(queuesPriorities[i].size()) != familiesQueueCount[i])
			throw std::runtime_error("LogicalDeviceCoreInternal Contructor Error: Queue priorities to queue count mismatch!");

		VkDeviceQueueCreateInfo add{};
		add.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		add.queueFamilyIndex = uniqueQueueFamilies[i];
		add.queueCount = familiesQueueCount[i];
		add.pQueuePriorities = queuesPriorities[i].data();

		queueCreateInfo.push_back(add);
	}

	VkPhysicalDeviceFeatures vulkan10Features{};
	vulkan10Features = CompileRequestedVulkan10Features(initData.creationInfo.vulkan10Features);

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<std::uint32_t>(queueCreateInfo.size());
	createInfo.pQueueCreateInfos = queueCreateInfo.data();

	createInfo.pEnabledFeatures = &vulkan10Features;

	auto deviceRequestedExtensions = CompileRequestedExtensions(initData.creationInfo.requestedExtensions);

	if (!deviceRequestedExtensions.empty())
	{
		createInfo.enabledExtensionCount = static_cast<std::uint32_t>(deviceRequestedExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceRequestedExtensions.data();
	}

	if (vkCreateDevice(initData.physicalDevice, &createInfo, nullptr, &_logicalDevice) != VK_SUCCESS)
		throw std::runtime_error("LogicalDeviceCoreInternal Contructor Error: Program failed to create a logical device!");

	_queues.resize(queuesCreateData.size(), { VK_NULL_HANDLE, std::numeric_limits<std::uint32_t>::max() });
	std::vector<std::uint32_t> queuesFamilesGot;
	queuesFamilesGot.resize(uniqueQueueFamilies.size(), 0);

	for (size_t i = 0; i < queuesCreateData.size(); i++)
	{
		bool found = false;
		std::uint32_t queueFamily = queuesCreateData[i].queueFamily;
		std::uint32_t queueIndex = std::numeric_limits<std::uint32_t>::max();

		_queues[i].second = queueFamily;

		for (size_t j = 0; j < uniqueQueueFamilies.size(); j++)
		{
			if (queueFamily == uniqueQueueFamilies[j])
			{
				found = true;
				queueIndex = queuesFamilesGot[j]++;
				break;
			}
		}

		if (!found)
			throw std::runtime_error("LogicalDeviceCoreInternal Contructor Error: Program failed to find family of a queue!");

		vkGetDeviceQueue(_logicalDevice, queueFamily, queueIndex, &_queues[i].first);

		if (_queues[i].first == VK_NULL_HANDLE)
			throw std::runtime_error("LogicalDeviceCoreInternal Contructor Error: Program failed to get a device queue!");
	}
}

LogicalDeviceCoreInternal::~LogicalDeviceCoreInternal()
{
	if (_logicalDevice != VK_NULL_HANDLE)
		vkDestroyDevice(_logicalDevice, nullptr);
}

VkDevice LogicalDeviceCoreInternal::GetDevice() const
{
	return _logicalDevice;
}

std::vector<std::uint32_t> LogicalDeviceCoreInternal::GetQueueFamilies(const std::vector<size_t>& queueIDs) const
{
	std::vector<std::uint32_t> ret;
	ret.reserve(queueIDs.size());

	for (auto& ID : queueIDs)
	{
		if (ID >= _queues.size())
			throw std::runtime_error("LogicalDeviceCoreInternal::GetQueueFamilies Error: Program tried to read past the queues list!");

		std::uint32_t add = _queues[ID].second;

		auto it = std::find(ret.cbegin(), ret.cend(), add);

		if (it == ret.cend())
		{
			ret.push_back(add);
		}
	}

	ret.shrink_to_fit();

	return ret;
}

void LogicalDeviceCoreInternal::CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected,
	bool throwOnSwapchainExist, bool throwOnDeviceChange)
{
	auto& window = _windowList.GetWindowSimplifier(windowID);

	SwapchainInitData initData;

	initData.device = _logicalDevice;
	initData.surfacePresentMode = TranslatePresentMode(surfaceCreateInfo.surfacePresentMode);
	initData.format = TranslateDataFormatToVkFormat(surfaceCreateInfo.format);
	if (createProtected)
		initData.flags |= VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR;
	initData.imageAmount = surfaceCreateInfo.imageAmount;

	initData.queueFamilies.reserve(surfaceCreateInfo.queuesUsingSwapchain.size());

	for (auto& queueID : surfaceCreateInfo.queuesUsingSwapchain)
	{
		if (queueID >= _queues.size())
			throw std::runtime_error("LogicalDeviceCoreInternal::CreateSwapchain Error: Program tried to access non-existent queue's data!");

		initData.queueFamilies.push_back(_queues[queueID].second);
	}

	std::sort(initData.queueFamilies.begin(), initData.queueFamilies.end());
	auto it = std::unique(initData.queueFamilies.begin(), initData.queueFamilies.end());
	initData.queueFamilies.erase(it, initData.queueFamilies.end());

	window.CreateSwapchain(initData, throwOnSwapchainExist, throwOnDeviceChange);
}

VkPhysicalDeviceFeatures LogicalDeviceCoreInternal::CompileRequestedVulkan10Features(VulkanDeviceFeatureFlags featureFlags)
{
	VkPhysicalDeviceFeatures ret{};

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_FULL_DRAW_INDEX_UINT32) == VULKAN10_DEVICE_FEATURE_FULL_DRAW_INDEX_UINT32)
		ret.fullDrawIndexUint32 = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_INDEPENDENT_BLEND) == VULKAN10_DEVICE_FEATURE_INDEPENDENT_BLEND)
		ret.independentBlend = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_FILL_MODE_NONSOLID) == VULKAN10_DEVICE_FEATURE_FILL_MODE_NONSOLID)
		ret.fillModeNonSolid = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SAMPLER_ANISOTROPY) == VULKAN10_DEVICE_FEATURE_SAMPLER_ANISOTROPY)
		ret.samplerAnisotropy = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ETC2) == VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ETC2)
		ret.textureCompressionETC2 = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR) == VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR)
		ret.textureCompressionASTC_LDR = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_BC) == VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_BC)
		ret.textureCompressionBC = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SHADER_FLOAT64) == VULKAN10_DEVICE_FEATURE_SHADER_FLOAT64)
		ret.shaderFloat64 = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SHADER_INT64) == VULKAN10_DEVICE_FEATURE_SHADER_INT64)
		ret.shaderInt64 = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SHADER_INT16) == VULKAN10_DEVICE_FEATURE_SHADER_INT16)
		ret.shaderInt16 = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_RESIDENCY) == VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_RESIDENCY)
		ret.shaderResourceResidency = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_MINIMUM_LOD) == VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_MINIMUM_LOD)
		ret.shaderResourceMinLod = VK_TRUE;

	return ret;
}

std::vector<const char*> LogicalDeviceCoreInternal::CompileRequestedExtensions(const DeviceExtensionList& deviceExtensionList) const
{
	std::vector<const char*> ret;

	CompileRequestedKHRExtensions(ret, deviceExtensionList.khrExtensions);

	return ret;
}

void LogicalDeviceCoreInternal::CompileRequestedKHRExtensions(std::vector<const char*>& requiredExtensions, DeviceExtensionFlags khrExtensions) const
{
	requiredExtensions.reserve(requiredExtensions.size() + (sizeof(DeviceExtensionFlags) << 3));

	if ((khrExtensions & DEVICE_KHR_EXTENSION_SWAPCHAIN) == DEVICE_KHR_EXTENSION_SWAPCHAIN)
		requiredExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

VkPresentModeKHR LogicalDeviceCoreInternal::TranslatePresentMode(SurfacePresentModeBits presentMode) const
{
	VkPresentModeKHR ret = VK_PRESENT_MODE_MAX_ENUM_KHR;

	switch (presentMode)
	{
	case PRESENT_MODE_FIFO_RELAXED:
		ret = VK_PRESENT_MODE_FIFO_RELAXED_KHR;
		break;
	case PRESENT_MODE_FIFO_STRICT:
		ret = VK_PRESENT_MODE_FIFO_KHR;
		break;
	case PRESENT_MODE_MAILBOX:
		ret = VK_PRESENT_MODE_MAILBOX_KHR;
		break;
	case PRESENT_MODE_IMMEDIATE:
		ret = VK_PRESENT_MODE_IMMEDIATE_KHR;
		break;
	default:
		throw std::runtime_error("LogicalDeviceCoreInternal::TranslatePresentMode Error: Program tried to translate an unknown value!");
	}

	return ret;
}
