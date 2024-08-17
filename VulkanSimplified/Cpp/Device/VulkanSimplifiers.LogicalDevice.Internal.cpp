module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.LogicalDevice.Internal;

LogicalDeviceInitData::LogicalDeviceInitData()
{
	physicalDevice = VK_NULL_HANDLE;

	apiVersion = 0;
	padding = 0;
}

LogicalDeviceInternal::LogicalDeviceInternal(const LogicalDeviceInitData& initData, WindowListInternal& windowList) : _windowList(windowList)
{
	_logicalDevice = VK_NULL_HANDLE;
	_physicalDevice = initData.physicalDevice;

	_physicalDeviceName = initData.physicalDeviceName;
	_logicalDeviceName = initData.creationInfo.logicalDeviceName;
	_apiVersion = initData.apiVersion;
	_padding = 0;

	auto& queuesCreateData = initData.creationInfo.queuesCreateInfo;

	if (queuesCreateData.empty())
		throw std::runtime_error("LogicalDeviceInternal Contructor Error: Program tried to create a device with no queues!");

	std::vector<std::pair<std::uint32_t, bool>> uniqueQueueFamilies;
	std::vector<std::uint32_t> familiesQueueCount;
	uniqueQueueFamilies.reserve(queuesCreateData.size());
	familiesQueueCount.reserve(queuesCreateData.size());

	for (size_t i = 0; i < queuesCreateData.size(); i++)
	{
		bool found = false;
		bool isProtectedQueue = GetProtectedFlagsValue(queuesCreateData[i].queueCreationFlags);
		std::uint32_t queueFamily = queuesCreateData[i].queueFamily;

		if (isProtectedQueue && initData.apiVersion < VK_MAKE_API_VERSION(0, 1, 1, 0))
			throw std::runtime_error("LogicalDeviceInternal Contructor Error: Protected queues require vulkan api version of 1.1.0 or higher!");

		for (size_t j = 0; j < uniqueQueueFamilies.size(); j++)
		{
			if (queueFamily == uniqueQueueFamilies[j].first && isProtectedQueue == uniqueQueueFamilies[j].second)
			{
				found = true;
				familiesQueueCount[j]++;
				break;
			}
		}

		if (!found)
		{
			uniqueQueueFamilies.push_back({ queueFamily, isProtectedQueue });
			familiesQueueCount.push_back(1);
		}
	}

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfo;
	std::vector<std::vector<float>> queuesPriorities;

	queueCreateInfo.reserve(uniqueQueueFamilies.size());
	queuesPriorities.resize(uniqueQueueFamilies.size());

	for (size_t i = 0; i < uniqueQueueFamilies.size(); i++)
	{
		queuesPriorities[i].reserve(uniqueQueueFamilies[i].first);

		for (size_t j = 0; j < queuesCreateData.size(); j++)
		{
			bool isProtectedQueue = GetProtectedFlagsValue(queuesCreateData[j].queueCreationFlags);
			std::uint32_t queueFamily = queuesCreateData[j].queueFamily;

			if (queueFamily == uniqueQueueFamilies[i].first && isProtectedQueue == uniqueQueueFamilies[i].second)
			{
				queuesPriorities[i].push_back(queuesCreateData[j].queuePriority);
			}
		}

		if (static_cast<std::uint32_t>(queuesPriorities[i].size()) != familiesQueueCount[i])
			throw std::runtime_error("LogicalDeviceInternal Contructor Error: Queue priorities to queue count mismatch!");

		VkDeviceQueueCreateInfo add{};
		add.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		if (uniqueQueueFamilies[i].second)
			add.flags |= VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
		add.queueFamilyIndex = uniqueQueueFamilies[i].first;
		add.queueCount = familiesQueueCount[i];
		add.pQueuePriorities = queuesPriorities[i].data();

		queueCreateInfo.push_back(add);
	}

	VkPhysicalDeviceFeatures2 vulkan10Features{};
	vulkan10Features.features = CompileRequestedVulkan10Features(initData.creationInfo.vulkan10Features);

	VkPhysicalDeviceVulkan11Features vulkan11Features{};
	VkPhysicalDeviceVulkan12Features vulkan12Features{};
	VkPhysicalDeviceVulkan13Features vulkan13Features{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<std::uint32_t>(queueCreateInfo.size());
	createInfo.pQueueCreateInfos = queueCreateInfo.data();

	if (initData.apiVersion < VK_MAKE_API_VERSION(0, 1, 2, 0))
	{
		createInfo.pEnabledFeatures = &vulkan10Features.features;
	}
	else
	{
		vulkan11Features = CompileRequestedVulkan11Features(initData.creationInfo.vulkan11Features);
		vulkan12Features = CompileRequestedVulkan12Features(initData.creationInfo.vulkan12Features);

		createInfo.pNext = &vulkan10Features;
		vulkan10Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		vulkan10Features.pNext = &vulkan11Features;
		vulkan11Features.pNext = &vulkan12Features;

		if (initData.apiVersion >= VK_MAKE_API_VERSION(0, 1, 3, 0))
		{
			vulkan13Features = CompileRequestedVulkan13Features(initData.creationInfo.vulkan13Features);

			vulkan12Features.pNext = &vulkan13Features;
		}
	}

	auto deviceRequestedExtensions = CompileRequestedExtensions(initData.creationInfo.requestedExtensions);

	if (!deviceRequestedExtensions.empty())
	{
		createInfo.enabledExtensionCount = static_cast<std::uint32_t>(deviceRequestedExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceRequestedExtensions.data();
	}

	if (vkCreateDevice(initData.physicalDevice, &createInfo, nullptr, &_logicalDevice) != VK_SUCCESS)
		throw std::runtime_error("LogicalDeviceInternal Contructor Error: Program failed to create a logical device!");

	_queues.resize(queuesCreateData.size(), { VK_NULL_HANDLE, std::numeric_limits<std::uint32_t>::max() });
	std::vector<std::uint32_t> queuesFamilesGot;
	queuesFamilesGot.resize(uniqueQueueFamilies.size(), 0);

	for (size_t i = 0; i < queuesCreateData.size(); i++)
	{
		bool found = false;
		bool isProtectedQueue = GetProtectedFlagsValue(queuesCreateData[i].queueCreationFlags);
		std::uint32_t queueFamily = queuesCreateData[i].queueFamily;
		std::uint32_t queueIndex = std::numeric_limits<std::uint32_t>::max();

		_queues[i].second = queueFamily;

		for (size_t j = 0; j < uniqueQueueFamilies.size(); j++)
		{
			if (queueFamily == uniqueQueueFamilies[j].first && isProtectedQueue == uniqueQueueFamilies[j].second)
			{
				found = true;
				queueIndex = queuesFamilesGot[j]++;
				break;
			}
		}

		if (!found)
			throw std::runtime_error("LogicalDeviceInternal Contructor Error: Program failed to find family of a queue!");

		if (initData.apiVersion < VK_MAKE_API_VERSION(0, 1, 1, 0))
		{
			vkGetDeviceQueue(_logicalDevice, queueFamily, queueIndex, &_queues[i].first);
		}
		else
		{
			VkDeviceQueueInfo2 deviceQueueInfo2{};
			deviceQueueInfo2.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
			if (isProtectedQueue)
				deviceQueueInfo2.flags |= VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
			deviceQueueInfo2.queueFamilyIndex = queueFamily;
			deviceQueueInfo2.queueIndex = queueIndex;

			vkGetDeviceQueue2(_logicalDevice, &deviceQueueInfo2, &_queues[i].first);

			if (_queues[i].first == VK_NULL_HANDLE)
			{
				bool foundConcat = false;

				for (size_t j = 0; j < queueCreateInfo.size(); j++)
				{
					if (queueFamily == queueCreateInfo[j].queueFamilyIndex)
					{
						foundConcat = true;
						queueIndex += queueCreateInfo[j].queueCount;
						break;
					}
				}

				if (!foundConcat)
					throw std::runtime_error("LogicalDeviceInternal Contructor Error: Program failed to find combined list family of a queue!");

				deviceQueueInfo2.queueIndex = queueIndex;

				vkGetDeviceQueue2(_logicalDevice, &deviceQueueInfo2, &_queues[i].first);
			}
		}

		if (_queues[i].first == VK_NULL_HANDLE)
			throw std::runtime_error("LogicalDeviceInternal Contructor Error: Program failed to get a device queue!");
	}

}

LogicalDeviceInternal::~LogicalDeviceInternal()
{
	if (_logicalDevice != VK_NULL_HANDLE)
		vkDestroyDevice(_logicalDevice, nullptr);
}

void LogicalDeviceInternal::CreateSwapchain(IDObject<WindowPointer> windowID, const SwapchainCreationData& surfaceCreateInfo, bool createProtected,
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
			throw std::runtime_error("LogicalDeviceInternal::CreateSwapchain Error: Program tried to access non-existent queue's data!");

		initData.queueFamilies.push_back(_queues[queueID].second);
	}

	std::sort(initData.queueFamilies.begin(), initData.queueFamilies.end());
	auto it = std::unique(initData.queueFamilies.begin(), initData.queueFamilies.end());
	initData.queueFamilies.erase(it, initData.queueFamilies.end());

	window.CreateSwapchain(initData, throwOnSwapchainExist, throwOnDeviceChange);
}

bool LogicalDeviceInternal::GetProtectedFlagsValue(QueueCreationFlags queueFlags)
{
	if ((queueFlags & QUEUE_CREATION_CREATE_PROTECTED) == QUEUE_CREATION_CREATE_PROTECTED)
		return true;

	return false;
}

VkPhysicalDeviceFeatures LogicalDeviceInternal::CompileRequestedVulkan10Features(VulkanDeviceFeatureFlags featureFlags)
{
	VkPhysicalDeviceFeatures ret{};

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_FULL_DRAW_INDEX_UINT32) == VULKAN10_DEVICE_FEATURE_FULL_DRAW_INDEX_UINT32)
		ret.fullDrawIndexUint32 = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_INDEPENDENT_BLEND) == VULKAN10_DEVICE_FEATURE_INDEPENDENT_BLEND)
		ret.independentBlend = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_FILL_MODE_NONSOLID) == VULKAN10_DEVICE_FEATURE_FILL_MODE_NONSOLID)
		ret.fillModeNonSolid = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_MULTI_VIEWPORT) == VULKAN10_DEVICE_FEATURE_MULTI_VIEWPORT)
		ret.multiViewport = VK_TRUE;

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

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_BINDING) == VULKAN10_DEVICE_FEATURE_SPARSE_BINDING)
		ret.sparseBinding = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_BUFFER) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_BUFFER)
		ret.sparseResidencyBuffer = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE2D) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE2D)
		ret.sparseResidencyImage2D = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE3D) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE3D)
		ret.sparseResidencyImage3D = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_2_SAMPLES) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_2_SAMPLES)
		ret.sparseResidency2Samples = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_4_SAMPLES) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_4_SAMPLES)
		ret.sparseResidency4Samples = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_8_SAMPLES) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_8_SAMPLES)
		ret.sparseResidency8Samples = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_16_SAMPLES) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_16_SAMPLES)
		ret.sparseResidency16Samples = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_ALIASED) == VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_ALIASED)
		ret.sparseResidencyAliased = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_VARIABLE_MULTISAMPLE_RATE) == VULKAN10_DEVICE_FEATURE_VARIABLE_MULTISAMPLE_RATE)
		ret.variableMultisampleRate = VK_TRUE;

	if ((featureFlags & VULKAN10_DEVICE_FEATURE_INHERITED_QUERIES) == VULKAN10_DEVICE_FEATURE_INHERITED_QUERIES)
		ret.inheritedQueries = VK_TRUE;

	return ret;
}

VkPhysicalDeviceVulkan11Features LogicalDeviceInternal::CompileRequestedVulkan11Features(VulkanDeviceFeatureFlags featureFlags)
{
	VkPhysicalDeviceVulkan11Features ret{};
	ret.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;

	if ((featureFlags & VULKAN11_DEVICE_FEATURE_STORAGE_BUFFER_16BIT_ACCESS) == VULKAN11_DEVICE_FEATURE_STORAGE_BUFFER_16BIT_ACCESS)
		ret.storageBuffer16BitAccess = VK_TRUE;

	if ((featureFlags & VULKAN11_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_16BIT_ACCESS) == VULKAN11_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_16BIT_ACCESS)
		ret.uniformAndStorageBuffer16BitAccess = VK_TRUE;

	if ((featureFlags & VULKAN11_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_16BIT) == VULKAN11_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_16BIT)
		ret.storagePushConstant16 = VK_TRUE;

	if ((featureFlags & VULKAN11_DEVICE_FEATURE_STORAGE_INPUT_OUTPUT_16BIT) == VULKAN11_DEVICE_FEATURE_STORAGE_INPUT_OUTPUT_16BIT)
		ret.storageInputOutput16 = VK_TRUE;

	if ((featureFlags & VULKAN11_DEVICE_FEATURE_MULTIVIEW) == VULKAN11_DEVICE_FEATURE_MULTIVIEW)
		ret.multiview = VK_TRUE;

	return ret;
}

VkPhysicalDeviceVulkan12Features LogicalDeviceInternal::CompileRequestedVulkan12Features(VulkanDeviceFeatureFlags featureFlags)
{
	VkPhysicalDeviceVulkan12Features ret{};
	ret.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_STORAGE_BUFFER_8BIT_ACCESS) == VULKAN12_DEVICE_FEATURE_STORAGE_BUFFER_8BIT_ACCESS)
		ret.storageBuffer8BitAccess = VK_TRUE;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_8BIT_ACCESS) == VULKAN12_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_8BIT_ACCESS)
		ret.uniformAndStorageBuffer8BitAccess = VK_TRUE;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_8BIT) == VULKAN12_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_8BIT)
		ret.storagePushConstant8 = VK_TRUE;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_SHADER_BUFFER_INT64_ATOMICS) == VULKAN12_DEVICE_FEATURE_SHADER_BUFFER_INT64_ATOMICS)
		ret.shaderBufferInt64Atomics = VK_TRUE;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_SHADER_SHARED_INT64_ATOMICS) == VULKAN12_DEVICE_FEATURE_SHADER_SHARED_INT64_ATOMICS)
		ret.shaderSharedInt64Atomics = VK_TRUE;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_SHADER_FLOAT_16BIT) == VULKAN12_DEVICE_FEATURE_SHADER_FLOAT_16BIT)
		ret.shaderFloat16 = VK_TRUE;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_SHADER_INT_8BIT) == VULKAN12_DEVICE_FEATURE_SHADER_INT_8BIT)
		ret.shaderInt8 = VK_TRUE;

	if ((featureFlags & VULKAN12_DEVICE_FEATURE_SCALAR_BLOCK_LAYOUT) == VULKAN12_DEVICE_FEATURE_SCALAR_BLOCK_LAYOUT)
		ret.scalarBlockLayout = VK_TRUE;

	return ret;
}

VkPhysicalDeviceVulkan13Features LogicalDeviceInternal::CompileRequestedVulkan13Features(VulkanDeviceFeatureFlags featureFlags)
{
	VkPhysicalDeviceVulkan13Features ret{};
	ret.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;

	if ((featureFlags & VULKAN13_DEVICE_FEATURE_SYNCHRONIZATION2) == VULKAN13_DEVICE_FEATURE_SYNCHRONIZATION2)
		ret.synchronization2 = VK_TRUE;

	if ((featureFlags & VULKAN13_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_HDR) == VULKAN13_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_HDR)
		ret.textureCompressionASTC_HDR = VK_TRUE;

	if ((featureFlags & VULKAN13_DEVICE_FEATURE_MAINTENANCE4) == VULKAN13_DEVICE_FEATURE_MAINTENANCE4)
		ret.maintenance4 = VK_TRUE;

	return ret;
}

std::vector<const char*> LogicalDeviceInternal::CompileRequestedExtensions(const RequestedExtensionList& deviceExtensionList) const
{
	std::vector<const char*> ret;

	CompileRequestedKHRExtensions(ret, deviceExtensionList.khrExtensions);

	return ret;
}

void LogicalDeviceInternal::CompileRequestedKHRExtensions(std::vector<const char*>& requiredExtensions, DeviceExtensionFlags khrExtensions) const
{
	requiredExtensions.reserve(requiredExtensions.size() + (sizeof(DeviceExtensionFlags) << 3));

	if ((khrExtensions & DEVICE_KHR_EXTENSION_SWAPCHAIN) == DEVICE_KHR_EXTENSION_SWAPCHAIN)
		requiredExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

VkPresentModeKHR LogicalDeviceInternal::TranslatePresentMode(SurfacePresentModeBits presentMode) const
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
		throw std::runtime_error("LogicalDeviceInternal::TranslatePresentMode Error: Program tried to translate an unknown value!");
	}

	return ret;
}
