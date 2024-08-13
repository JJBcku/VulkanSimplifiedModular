	module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.PhysicalDevice.Internal;

QueueSupportSavedData::QueueSupportSavedData()
{
	surface = VK_NULL_HANDLE;
}

QueueSupportSavedData::QueueSupportSavedData(VkSurfaceKHR initSurface, const SurfaceSupportData& initQueueData) : surface(initSurface), queueData(initQueueData)
{
}

PhysicalDeviceInternal::PhysicalDeviceInternal(VkPhysicalDevice physicalDevice, std::uint32_t instanceVulkanVersion, WindowListInternal& windowList) : _physicalDevice(physicalDevice),
_windowList(windowList)
{
	_device10features = 0;
	_device11features = 0;
	_device12features = 0;
	_device13features = 0;

	VkPhysicalDeviceProperties vulkanProperties{};

	vkGetPhysicalDeviceProperties(_physicalDevice, &vulkanProperties);

	_vulkanProperties.apiMaxSupportedVersion = vulkanProperties.apiVersion;
	_vulkanProperties.driverVersion = vulkanProperties.driverVersion;
	_vulkanProperties.vendorID = vulkanProperties.vendorID;
	_vulkanProperties.deviceID = vulkanProperties.deviceID;
	_vulkanProperties.deviceType = GetDeviceType(vulkanProperties.deviceType);
	_vulkanProperties.deviceName = std::string(vulkanProperties.deviceName);

	for (size_t i = 0; i < _vulkanProperties.pipelineCacheID.size(); i++)
		_vulkanProperties.pipelineCacheID[i] = vulkanProperties.pipelineCacheUUID[i];

	_vulkanProperties.device10Limits = CompileVulkan10DeviceLimits(vulkanProperties.limits);

	if (instanceVulkanVersion < VK_MAKE_API_VERSION(0, 1, 2, 0) || _vulkanProperties.apiMaxSupportedVersion < VK_MAKE_API_VERSION(0, 1, 2, 0))
	{
		VkPhysicalDeviceFeatures vulkan10Features{};
		
		vkGetPhysicalDeviceFeatures(_physicalDevice, &vulkan10Features);

		_device10features = CompileVulkan10DeviceFeatures(vulkan10Features);
	}
	else
	{
		VkPhysicalDeviceFeatures2 vulkan10Features{};
		VkPhysicalDeviceVulkan11Features vulkan11Features{};
		VkPhysicalDeviceVulkan12Features vulkan12Features{};
		VkPhysicalDeviceVulkan13Features vulkan13Features{};

		vulkan10Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		vulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
		vulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

		vulkan10Features.pNext = &vulkan11Features;
		vulkan11Features.pNext = &vulkan12Features;

		if (instanceVulkanVersion >= VK_MAKE_API_VERSION(0, 1, 3, 0) && _vulkanProperties.apiMaxSupportedVersion >= VK_MAKE_API_VERSION(0, 1, 3, 0))
		{
			vulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
			vulkan12Features.pNext = &vulkan13Features;
		}

		vkGetPhysicalDeviceFeatures2(_physicalDevice, &vulkan10Features);

		_device10features = CompileVulkan10DeviceFeatures(vulkan10Features.features);
		_device11features = CompileVulkan11DeviceFeatures(vulkan11Features);
		_device12features = CompileVulkan12DeviceFeatures(vulkan12Features);

		if (instanceVulkanVersion >= VK_MAKE_API_VERSION(0, 1, 3, 0) && _vulkanProperties.apiMaxSupportedVersion >= VK_MAKE_API_VERSION(0, 1, 3, 0))
			_device13features = CompileVulkan13DeviceFeatures(vulkan13Features);
	}

	std::uint32_t queueCount = 0;
	std::vector<VkQueueFamilyProperties> queueFamilies;

	vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueCount, nullptr);

	if (queueCount > 0)
	{
		queueFamilies.resize(queueCount);
		vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueCount, queueFamilies.data());

		_vulkanProperties.queueFamilies.resize(queueCount);

		for (size_t i = 0; i < queueFamilies.size(); i++)
		{
			auto& family = queueFamilies[i];
			auto& queueData = _vulkanProperties.queueFamilies[i];

			queueData.queueTypes = family.queueFlags;
			queueData.queueCount = family.queueCount;
			queueData.timespampValidBits = family.timestampValidBits;
			queueData.minImageTransferGranularityWidth = family.minImageTransferGranularity.width;
			queueData.minImageTransferGranularityHeight = family.minImageTransferGranularity.height;
			queueData.minImageTransferGranularityDepth = family.minImageTransferGranularity.depth;
		}
	}

	std::vector<VkExtensionProperties> availableExtensions;
	std::uint32_t size = 0;

	vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &size, nullptr);

	if (size > 0)
	{
		availableExtensions.resize(size);

		vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &size, availableExtensions.data());

		_vulkanProperties.deviceExtensions.khrExtensions = CompileKHRDeviceExtensionList(availableExtensions);
	}

	_vulkanProperties.deviceFormatsSupport = CompileFormatsSupportedFeatures();
}

PhysicalDeviceInternal::~PhysicalDeviceInternal()
{
}

DeviceVulkanPropertiesSimplified PhysicalDeviceInternal::GetVulkanPropertiesSimplified() const
{
	return _vulkanProperties;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::GetVulkan10Features() const
{
	return _device10features;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::GetVulkan11Features() const
{
	return _device11features;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::GetVulkan12Features() const
{
	return _device12features;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::GetVulkan13Features() const
{
	return _device13features;
}

VkPhysicalDevice PhysicalDeviceInternal::GetPhysicalDevice() const
{
	return _physicalDevice;
}

SurfaceSupportData PhysicalDeviceInternal::GetSurfaceSupport(IDObject<WindowPointer> windowID)
{
	auto& window = _windowList.GetWindowSimplifier(windowID);
	auto surface = window.GetSurface();

	SurfaceSupportData ret;

	ret.queuePresentingSupport.resize(_vulkanProperties.queueFamilies.size(), false);

	for (size_t i = 0; i < ret.queuePresentingSupport.size(); i++)
	{
		VkBool32 presentationSupport = VK_FALSE;

		if (vkGetPhysicalDeviceSurfaceSupportKHR(_physicalDevice, static_cast<uint32_t>(i), surface, &presentationSupport) != VK_SUCCESS)
			throw std::runtime_error("PhysicalDeviceInternal::GetSurfaceSupport Error: Program failed to query a queues presentation support!");

		ret.queuePresentingSupport[i] = presentationSupport == VK_TRUE;
	}

	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities{};
		
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice, surface, &surfaceCapabilities);

		ret.minImageCount = surfaceCapabilities.minImageCount;
		ret.maxImageCount = surfaceCapabilities.maxImageCount;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) == VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_TRANSFER_SRC;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) == VK_IMAGE_USAGE_TRANSFER_DST_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_TRANSFER_DST;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_SAMPLED_BIT) == VK_IMAGE_USAGE_SAMPLED_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_SAMPLED;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_STORAGE_BIT) == VK_IMAGE_USAGE_STORAGE_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_STORAGE;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) == VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_COLOR_ATTACHMENT;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT) == VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_TRANSIENT_ATTACHMENT;

		if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT) == VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
			ret.surfaceUsageFlags |= IMAGE_USAGE_INPUT_ATTACHMENT;

		std::vector<VkPresentModeKHR> surfacePresentModes;
		std::uint32_t size = 0;

		vkGetPhysicalDeviceSurfacePresentModesKHR(_physicalDevice, surface, &size, nullptr);

		if (size > 0)
		{
			surfacePresentModes.resize(size);
			vkGetPhysicalDeviceSurfacePresentModesKHR(_physicalDevice, surface, &size, surfacePresentModes.data());

			for (auto& presentMode : surfacePresentModes)
			{
				if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
					ret.surfacePresentModes |= PRESENT_MODE_IMMEDIATE;

				if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
					ret.surfacePresentModes |= PRESENT_MODE_MAILBOX;

				if (presentMode == VK_PRESENT_MODE_FIFO_KHR)
					ret.surfacePresentModes |= PRESENT_MODE_FIFO_STRICT;

				if (presentMode == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
					ret.surfacePresentModes |= PRESENT_MODE_FIFO_RELAXED;
			}
		}

		size = 0;

		vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, surface, &size, nullptr);

		std::vector<VkSurfaceFormatKHR> supportedSwapchainFormats;

		if (size > 0)
		{
			supportedSwapchainFormats.resize(size);

			vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, surface, &size, supportedSwapchainFormats.data());

			for (auto& formatData : supportedSwapchainFormats)
			{
				if (formatData.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
				{
					auto& srgb = ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace;

					if (formatData.format == VK_FORMAT_A1R5G5B5_UNORM_PACK16)
						srgb.fifthSet |= DATA_FORMAT_A1_RGB5_UNORM_PACK16;

					if (formatData.format == VK_FORMAT_A2B10G10R10_UNORM_PACK32)
						srgb.fifthSet |= DATA_FORMAT_A2_BGR10_UNORM_PACK32;

					if (formatData.format == VK_FORMAT_A2R10G10B10_UNORM_PACK32)
						srgb.fifthSet |= DATA_FORMAT_A2_RGB10_UNORM_PACK32;

					if (formatData.format == VK_FORMAT_A8B8G8R8_SNORM_PACK32)
						srgb.fifthSet |= DATA_FORMAT_ABGR8_SNORM_PACK32;

					if (formatData.format == VK_FORMAT_A8B8G8R8_SRGB_PACK32)
						srgb.fifthSet |= DATA_FORMAT_ABGR8_SRGB_PACK32;

					if (formatData.format == VK_FORMAT_A8B8G8R8_UNORM_PACK32)
						srgb.fifthSet |= DATA_FORMAT_ABGR8_UNORM_PACK32;

					if (formatData.format == VK_FORMAT_B10G11R11_UFLOAT_PACK32)
						srgb.secondSet |= DATA_FORMAT_B10_GR11_UFLOAT_PACK32;

					if (formatData.format == VK_FORMAT_B4G4R4A4_UNORM_PACK16)
						srgb.secondSet |= DATA_FORMAT_BGRA4_UNORM_PACK16;

					if (formatData.format == VK_FORMAT_B5G5R5A1_UNORM_PACK16)
						srgb.secondSet |= DATA_FORMAT_BGR5_A1_UNORM_PACK16;

					if (formatData.format == VK_FORMAT_B5G6R5_UNORM_PACK16)
						srgb.secondSet |= DATA_FORMAT_B5_G6_R5_UNORM_PACK16;

					if (formatData.format == VK_FORMAT_B8G8R8A8_SNORM)
						srgb.secondSet |= DATA_FORMAT_BGRA8_SNORM;

					if (formatData.format == VK_FORMAT_B8G8R8A8_SRGB)
						srgb.secondSet |= DATA_FORMAT_BGRA8_SRGB;

					if (formatData.format == VK_FORMAT_B8G8R8A8_UNORM)
						srgb.thirdSet |= DATA_FORMAT_BGRA8_UNORM;

					if (formatData.format == VK_FORMAT_R16G16B16A16_SFLOAT)
						srgb.fifthSet |= DATA_FORMAT_RGBA16_SFLOAT;

					if (formatData.format == VK_FORMAT_R16G16B16A16_SNORM)
						srgb.fifthSet |= DATA_FORMAT_RGBA16_SNORM;

					if (formatData.format == VK_FORMAT_B8G8R8A8_UNORM)
						srgb.fifthSet |= DATA_FORMAT_RGBA16_UNORM;

					if (formatData.format == VK_FORMAT_R4G4B4A4_UNORM_PACK16)
						srgb.sixthSet |= DATA_FORMAT_RGBA4_UNORM_PACK16;

					if (formatData.format == VK_FORMAT_R5G5B5A1_UNORM_PACK16)
						srgb.sixthSet |= DATA_FORMAT_RGB5_A1_UNORM_PACK16;

					if (formatData.format == VK_FORMAT_R5G6B5_UNORM_PACK16)
						srgb.sixthSet |= DATA_FORMAT_R5_G6_B5_UNORM_PACK16;

					if (formatData.format == VK_FORMAT_R8_UNORM)
						srgb.sixthSet |= DATA_FORMAT_R8_UNORM;

					if (formatData.format == VK_FORMAT_R8G8B8A8_SNORM)
						srgb.seventhSet |= DATA_FORMAT_RGBA8_SNORM;

					if (formatData.format == VK_FORMAT_R8G8B8A8_SRGB)
						srgb.seventhSet |= DATA_FORMAT_RGBA8_SRGB;

					if (formatData.format == VK_FORMAT_R8G8B8A8_UNORM)
						srgb.seventhSet |= DATA_FORMAT_RGBA8_UNORM;
				}
			}
		}
	}

	return ret;
}

DeviceType PhysicalDeviceInternal::GetDeviceType(const VkPhysicalDeviceType& deviceType) const
{
	DeviceType ret = DeviceType::OTHER;

	switch (deviceType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_OTHER:
		break;
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		ret = DeviceType::INTERGRATED_GPU;
		break;
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		ret = DeviceType::DISCRETE_GPU;
		break;
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		ret = DeviceType::VIRTUAL_GPU;
		break;
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
		ret = DeviceType::CPU;
		break;
	case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:
	default:
		break;
	}

	return ret;
}

Vulkan10DeviceLimits PhysicalDeviceInternal::CompileVulkan10DeviceLimits(const VkPhysicalDeviceLimits& deviceLimits) const
{
	Vulkan10DeviceLimits ret;

	ret.maxImageSizes.maxImageDimension1D = deviceLimits.maxImageDimension1D;
	ret.maxImageSizes.maxImageDimension2D = deviceLimits.maxImageDimension2D;
	ret.maxImageSizes.maxImageDimension3D = deviceLimits.maxImageDimension3D;
	ret.maxImageSizes.maxImageArrayLayers = deviceLimits.maxImageArrayLayers;

	ret.maxUniformBufferRange = deviceLimits.maxUniformBufferRange;
	ret.maxStorageBufferRange = deviceLimits.maxStorageBufferRange;
	ret.maxPushConstantsSize = deviceLimits.maxPushConstantsSize;

	ret.maxMemoryAllocationCount = deviceLimits.maxMemoryAllocationCount;
	ret.maxSamplerAllocationCount = deviceLimits.maxSamplerAllocationCount;

	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxBoundDescriptorSets = deviceLimits.maxBoundDescriptorSets;
	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorSamplers = deviceLimits.maxPerStageDescriptorSamplers;
	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorUniformBuffers = deviceLimits.maxPerStageDescriptorUniformBuffers;
	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorStorageBuffers = deviceLimits.maxPerStageDescriptorStorageBuffers;
	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorSampledImages = deviceLimits.maxPerStageDescriptorSampledImages;
	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorStorageImages = deviceLimits.maxPerStageDescriptorStorageImages;
	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorInputAttachments = deviceLimits.maxPerStageDescriptorInputAttachments;
	ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageResources = deviceLimits.maxPerStageResources;

	ret.descriptorSetLimits.maxDescriptorSetSamplers = deviceLimits.maxDescriptorSetSamplers;
	ret.descriptorSetLimits.maxDescriptorSetUniformBuffers = deviceLimits.maxDescriptorSetUniformBuffers;
	ret.descriptorSetLimits.maxDescriptorSetUniformBuffersDynamic = deviceLimits.maxDescriptorSetUniformBuffersDynamic;
	ret.descriptorSetLimits.maxDescriptorSetStorageBuffers = deviceLimits.maxDescriptorSetStorageBuffers;
	ret.descriptorSetLimits.maxDescriptorSetStorageBuffersDynamic = deviceLimits.maxDescriptorSetStorageBuffersDynamic;
	ret.descriptorSetLimits.maxDescriptorSetSampledImages = deviceLimits.maxDescriptorSetSampledImages;
	ret.descriptorSetLimits.maxDescriptorSetStorageImages = deviceLimits.maxDescriptorSetStorageImages;
	ret.descriptorSetLimits.maxDescriptorSetInputAttachments = deviceLimits.maxDescriptorSetInputAttachments;

	ret.vertexShaderLimit.maxVertexInputAttributes = deviceLimits.maxVertexInputAttributes;
	ret.vertexShaderLimit.maxVertexInputBindings = deviceLimits.maxVertexInputBindings;
	ret.vertexShaderLimit.maxVertexInputAttributeOffset = deviceLimits.maxVertexInputAttributeOffset;
	ret.vertexShaderLimit.maxVertexInputBindingStride = deviceLimits.maxVertexInputBindingStride;
	ret.vertexShaderLimit.maxVertexOutputComponents = deviceLimits.maxVertexOutputComponents;

	ret.fragmentShaderLimit.maxFragmentInputComponents = deviceLimits.maxFragmentInputComponents;
	ret.fragmentShaderLimit.maxFragmentOutputAttachments = deviceLimits.maxFragmentOutputAttachments;
	ret.fragmentShaderLimit.maxFragmentDualSrcAttachments = deviceLimits.maxFragmentDualSrcAttachments;
	ret.fragmentShaderLimit.maxFragmentCombinedOutputResources = deviceLimits.maxFragmentCombinedOutputResources;

	ret.subPixelPrecisionBits = deviceLimits.subPixelPrecisionBits;
	ret.mipmapPrecisionBits = deviceLimits.mipmapPrecisionBits;

	ret.maxDrawIndexedIndexValue = deviceLimits.maxDrawIndexedIndexValue;

	ret.maxSamplerLodBias = static_cast<double>(deviceLimits.maxSamplerLodBias);
	ret.maxSamplerAnisotropy = static_cast<double>(deviceLimits.maxSamplerAnisotropy);

	ret.viewportLimits.maxViewports = deviceLimits.maxViewports;
	ret.viewportLimits.maxViewportDimensionsX = deviceLimits.maxViewportDimensions[0];
	ret.viewportLimits.maxViewportDimensionsY = deviceLimits.maxViewportDimensions[1];
	ret.viewportLimits.viewportBoundsRangeMin = static_cast<double>(deviceLimits.viewportBoundsRange[0]);
	ret.viewportLimits.viewportBoundsRangeMax = static_cast<double>(deviceLimits.viewportBoundsRange[1]);
	ret.viewportLimits.viewportSubPixelBits = deviceLimits.viewportSubPixelBits;

	ret.framebufferLimits.maxFramebufferWidth = deviceLimits.maxFramebufferWidth;
	ret.framebufferLimits.maxFramebufferHeight = deviceLimits.maxFramebufferHeight;
	ret.framebufferLimits.maxFramebufferLayers = deviceLimits.maxFramebufferLayers;
	ret.framebufferLimits.framebufferColorSampleCounts = deviceLimits.framebufferColorSampleCounts;
	ret.framebufferLimits.framebufferDepthSampleCounts = deviceLimits.framebufferDepthSampleCounts;
	ret.framebufferLimits.framebufferStencilSampleCounts = deviceLimits.framebufferStencilSampleCounts;
	ret.framebufferLimits.framebufferNoAttachmentsSampleCounts = deviceLimits.framebufferNoAttachmentsSampleCounts;

	ret.maxColorAttachments = deviceLimits.maxColorAttachments;

	ret.samplingLimits.sampledImageColorSampleCounts = deviceLimits.sampledImageColorSampleCounts;
	ret.samplingLimits.sampledImageIntegerSampleCounts = deviceLimits.sampledImageIntegerSampleCounts;
	ret.samplingLimits.sampledImageDepthSampleCounts = deviceLimits.sampledImageDepthSampleCounts;
	ret.samplingLimits.sampledImageStencilSampleCounts = deviceLimits.sampledImageStencilSampleCounts;
	ret.samplingLimits.storageImageSampleCounts = deviceLimits.storageImageSampleCounts;

	return ret;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::CompileVulkan10DeviceFeatures(const VkPhysicalDeviceFeatures& deviceFeatures) const
{
	VulkanDeviceFeatureFlags ret = 0;

	if (deviceFeatures.fullDrawIndexUint32 == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_FULL_DRAW_INDEX_UINT32;

	if (deviceFeatures.independentBlend == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_INDEPENDENT_BLEND;

	if (deviceFeatures.fillModeNonSolid == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_FILL_MODE_NONSOLID;

	if (deviceFeatures.multiViewport == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_MULTI_VIEWPORT;

	if (deviceFeatures.samplerAnisotropy == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SAMPLER_ANISOTROPY;

	if (deviceFeatures.textureCompressionETC2 == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ETC2;

	if (deviceFeatures.textureCompressionASTC_LDR == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR;

	if (deviceFeatures.textureCompressionBC == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_BC;

	if (deviceFeatures.shaderFloat64 == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SHADER_FLOAT64;

	if (deviceFeatures.shaderInt64 == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SHADER_INT64;

	if (deviceFeatures.shaderInt16 == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SHADER_INT16;

	if (deviceFeatures.shaderResourceResidency == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_RESIDENCY;

	if (deviceFeatures.shaderResourceMinLod == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_MINIMUM_LOD;

	if (deviceFeatures.sparseBinding == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_BINDING;

	if (deviceFeatures.sparseResidencyBuffer == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_BUFFER;

	if (deviceFeatures.sparseResidencyImage2D == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE2D;

	if (deviceFeatures.sparseResidencyImage3D == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE3D;

	if (deviceFeatures.sparseResidency2Samples == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_2_SAMPLES;

	if (deviceFeatures.sparseResidency4Samples == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_4_SAMPLES;

	if (deviceFeatures.sparseResidency8Samples == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_8_SAMPLES;

	if (deviceFeatures.sparseResidency16Samples == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_16_SAMPLES;

	if (deviceFeatures.sparseResidencyAliased == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_ALIASED;

	if (deviceFeatures.variableMultisampleRate == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_VARIABLE_MULTISAMPLE_RATE;

	if (deviceFeatures.inheritedQueries == VK_TRUE)
		ret |= VULKAN10_DEVICE_FEATURE_INHERITED_QUERIES;

	return ret;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::CompileVulkan11DeviceFeatures(const VkPhysicalDeviceVulkan11Features& deviceFeatures) const
{
	VulkanDeviceFeatureFlags ret = 0;

	if (deviceFeatures.storageBuffer16BitAccess == VK_TRUE)
		ret |= VULKAN11_DEVICE_FEATURE_STORAGE_BUFFER_16BIT_ACCESS;

	if (deviceFeatures.uniformAndStorageBuffer16BitAccess == VK_TRUE)
		ret |= VULKAN11_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_16BIT_ACCESS;

	if (deviceFeatures.storagePushConstant16 == VK_TRUE)
		ret |= VULKAN11_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_16BIT;

	if (deviceFeatures.storageInputOutput16 == VK_TRUE)
		ret |= VULKAN11_DEVICE_FEATURE_STORAGE_INPUT_OUTPUT_16BIT;

	if (deviceFeatures.multiview == VK_TRUE)
		ret |= VULKAN11_DEVICE_FEATURE_MULTIVIEW;

	return ret;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::CompileVulkan12DeviceFeatures(const VkPhysicalDeviceVulkan12Features& deviceFeatures) const
{
	VulkanDeviceFeatureFlags ret = 0;

	if (deviceFeatures.storageBuffer8BitAccess == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_STORAGE_BUFFER_8BIT_ACCESS;

	if (deviceFeatures.uniformAndStorageBuffer8BitAccess == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_8BIT_ACCESS;

	if (deviceFeatures.storagePushConstant8 == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_8BIT;

	if (deviceFeatures.shaderBufferInt64Atomics == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_SHADER_BUFFER_INT64_ATOMICS;

	if (deviceFeatures.shaderSharedInt64Atomics == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_SHADER_SHARED_INT64_ATOMICS;

	if (deviceFeatures.shaderFloat16 == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_SHADER_FLOAT_16BIT;

	if (deviceFeatures.shaderInt8 == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_SHADER_INT_8BIT;

	if (deviceFeatures.scalarBlockLayout == VK_TRUE)
		ret |= VULKAN12_DEVICE_FEATURE_SCALAR_BLOCK_LAYOUT;

	return ret;
}

VulkanDeviceFeatureFlags PhysicalDeviceInternal::CompileVulkan13DeviceFeatures(const VkPhysicalDeviceVulkan13Features& deviceFeatures) const
{
	VulkanDeviceFeatureFlags ret = 0;

	if (deviceFeatures.synchronization2 == VK_TRUE)
		ret |= VULKAN13_DEVICE_FEATURE_SYNCHRONIZATION2;

	if (deviceFeatures.textureCompressionASTC_HDR == VK_TRUE)
		ret |= VULKAN13_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_HDR;

	if (deviceFeatures.maintenance4 == VK_TRUE)
		ret |= VULKAN13_DEVICE_FEATURE_MAINTENANCE4;

	return ret;
}

DeviceExtensionFlags PhysicalDeviceInternal::CompileKHRDeviceExtensionList(const std::vector<VkExtensionProperties>& availableExtensions) const
{
	DeviceExtensionFlags ret = 0;

	for (size_t i = 0; i < availableExtensions.size(); i++)
	{
		const char* extensionName = availableExtensions[i].extensionName;

		if (std::strcmp(extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0)
		{
			ret |= DEVICE_KHR_EXTENSION_SWAPCHAIN;
		}
	}

	return ret;
}

FormatsSupportedFullFeatures PhysicalDeviceInternal::CompileFormatsSupportedFeatures() const
{
	FormatsSupportedFullFeatures ret;

	{
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A1_RGB5_UNORM_PACK16);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_BGR10_SINT_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_BGR10_SNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_BGR10_SSCALED_PACK32);

		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_BGR10_UINT_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_BGR10_UNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_BGR10_USCALED_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_RGB10_SINT_PACK32);

		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_RGB10_SNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_RGB10_SSCALED_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_RGB10_UINT_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_RGB10_UNORM_PACK32);

		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_A2_RGB10_USCALED_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ABGR8_SINT_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ABGR8_SNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ABGR8_SRGB_PACK32);

		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ABGR8_SSCALED_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ABGR8_UINT_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ABGR8_UNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ABGR8_USCALED_PACK32);

		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X10_SRGB_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X10_UNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X5_SRGB_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X5_UNORM_PACK32);

		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X6_SRGB_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X6_UNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X8_SRGB_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_10X8_UNORM_PACK32);

		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_12X10_SRGB_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_12X10_UNORM_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_12X10_SRGB_PACK32);
		GetFirstSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_12X10_UNORM_PACK32);
	}

	{
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_4X4_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_4X4_UNORM_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_5X4_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_5X4_UNORM_PACK32);

		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_5X5_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_5X5_UNORM_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_6X5_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_6X5_UNORM_PACK32);

		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_6X6_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_6X6_UNORM_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_8X5_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_8X5_UNORM_PACK32);

		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_8X6_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_8X6_UNORM_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_8X8_SRGB_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ASTC_8X8_UNORM_PACK32);

		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_B10_GR11_UFLOAT_PACK32);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_B10X6_G10X6_R10X6_G10X6_422_UNORM_4PACK16);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_B12X4_G12X4_R12X4_G12X4_422_UNORM_4PACK16);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRG16_422_UNORM);

		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA4_UNORM_PACK16);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGR5_A1_UNORM_PACK16);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_B5_G6_R5_UNORM_PACK16);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGR8_SINT);

		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGR8_SNORM);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGR8_SRGB);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGR8_UINT);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGR8_UNORM);

		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA8_SINT);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA8_SNORM);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA8_SRGB);
		GetSecondSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA8_SSCALED);
	}

	{
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA8_UINT);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA8_UNORM);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRA8_USCALED);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BGRG8_422_UNORM);

		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC1_RGB_SRGB_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC1_RGB_UNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC1_RGBA_SRGB_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC1_RGBA_UNORM_BLOCK);

		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC2_SRGB_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC2_UNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC3_SRGB_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC3_UNORM_BLOCK);

		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC4_SNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC4_UNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC5_SNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC5_UNORM_BLOCK);

		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC6H_SFLOAT_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC6H_UFLOAT_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC7_SRGB_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_BC7_UNORM_BLOCK);

		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_D16_UNORM);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_D16_UNORM_S8_UINT);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_D24_UNORM_S8_UINT);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_D32_SFLOAT);

		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_D32_SFLOAT_S8_UINT);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_E5_BGR9_UFLOAT_PACK32);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_EAC_R11_SNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_EAC_R11_UNORM_BLOCK);

		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_EAC_RG11_SNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_EAC_RG11_UNORM_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ETC2_RGB8_SRGB_BLOCK);
		GetThirdSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ETC2_RGB8_UNORM_BLOCK);
	}

	{
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ETC2_RGB8_A1_SRGB_BLOCK);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ETC2_RGB8_A1_UNORM_BLOCK);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ETC2_RGBA8_SRGB_BLOCK);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_ETC2_RGBA8_UNORM_BLOCK);

		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G10X6_BR10X6_2PLANE_420_UNORM_3PACK16);

		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G10X6_BR10X6_2PLANE_422_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G10X6_B10X6_G10X6_R10X6_422_UNORM_4PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16);

		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G12X4_BR12X4_2PLANE_420_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G12X4_BR12X4_2PLANE_422_UNORM_3PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G12X4_B12X4_G12X4_R12X4_422_UNORM_4PACK16);

		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G16_B16_R16_3PLANE_420_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G16_B16_R16_3PLANE_422_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G16_BR16_2PLANE_420_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G16_BR16_2PLANE_422_UNORM);

		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_GBGR16_422_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G8_B8_R8_3PLANE_420_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G8_B8_R8_3PLANE_422_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G8_B8_R8_3PLANE_444_UNORM);

		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G8_BR8_2PLANE_420_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_G8_BR8_2PLANE_422_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_GBGR8_422_UNORM);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R10X6_UNORM_PACK16);

		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R10X6_G10X6_UNORM_2PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R10X6_G10X6_B10X6_A10X6_UNORM_4PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R12X4_UNORM_PACK16);
		GetFourthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R12X4_G12X4_UNORM_2PACK16);
	}

	{
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R12X4_G12X4_B12X4_A12X4_UNORM_4PACK16);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R16_SFLOAT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R16_SINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R16_SNORM);

		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R16_SSCALED);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R16_UINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R16_UNORM);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R16_USCALED);

		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG16_SFLOAT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG16_SINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG16_SNORM);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG16_SSCALED);

		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG16_UINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG16_UNORM);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG16_USCALED);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB16_SFLOAT);

		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB16_SINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB16_SNORM);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB16_UINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB16_UNORM);

		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA16_SFLOAT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA16_SINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA16_SNORM);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA16_SSCALED);

		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA16_UINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA16_UNORM);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA16_USCALED);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R32_SFLOAT);

		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R32_SINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R32_UINT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R32_SFLOAT);
		GetFifthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R32_SINT);
	}

	{
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG32_UINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB32_SFLOAT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB32_SINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB32_UINT);

		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA32_SFLOAT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA32_SINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA32_UINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG4_UNORM_PACK8);

		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA4_UNORM_PACK16);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB5_A1_UNORM_PACK16);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R5_G6_B5_UNORM_PACK16);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R64_SFLOAT);

		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R64_SINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R64_UINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG64_SINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG64_UINT);

		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA64_SINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA64_UINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R8_SINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R8_SNORM);

		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R8_SRGB);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R8_SSCALED);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R8_UINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R8_UNORM);

		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_R8_USCALED);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG8_SINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG8_SNORM);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG8_SRGB);

		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG8_SSCALED);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG8_UINT);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG8_UNORM);
		GetSixthSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RG8_USCALED);
	}

	{
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB8_SINT);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB8_SNORM);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB8_SRGB);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB8_UINT);

		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGB8_UNORM);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA8_SINT);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA8_SNORM);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA8_SRGB);

		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA8_SSCALED);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA8_UINT);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA8_UNORM);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_RGBA8_USCALED);

		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_S8_UINT);
		GetSeventhSetsFormatsSupportedFeatures(ret, DATA_FORMAT_X8D24_UNORM_PACK32);
	}

	return ret;
}

void PhysicalDeviceInternal::GetFirstSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& formatsSupportedFeatures, DataFormatFirstFlagSetBits flagSetBit) const
{
	VkFormatProperties formatProperties{};
	VkFormat format = TranslateDataFormatFirstSetToVKFormat(flagSetBit);

	vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &formatProperties);

	{
		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.firstSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.firstSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.firstSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.firstSet |= flagSetBit;
	}

	{
		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.firstSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.firstSet |= flagSetBit;
	}

	{
		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.firstSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.firstSet |= flagSetBit;
	}
}

void PhysicalDeviceInternal::GetSecondSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& formatsSupportedFeatures, DataFormatSecondFlagSetBits flagSetBit) const
{
	VkFormatProperties formatProperties{};
	VkFormat format = TranslateDataFormatSecondSetToVKFormat(flagSetBit);

	vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &formatProperties);

	{
		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.secondSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.secondSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.secondSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.secondSet |= flagSetBit;
	}

	{
		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.secondSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.secondSet |= flagSetBit;
	}

	{
		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.secondSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.secondSet |= flagSetBit;
	}
}

void PhysicalDeviceInternal::GetThirdSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& formatsSupportedFeatures, DataFormatThirdFlagSetBits flagSetBit) const
{
	VkFormatProperties formatProperties{};
	VkFormat format = TranslateDataFormatThirdSetToVKFormat(flagSetBit);

	vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &formatProperties);

	{
		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.thirdSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.thirdSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.thirdSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.thirdSet |= flagSetBit;
	}

	{
		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.thirdSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.thirdSet |= flagSetBit;
	}

	{
		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.thirdSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.thirdSet |= flagSetBit;
	}
}

void PhysicalDeviceInternal::GetFourthSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& formatsSupportedFeatures, DataFormatFourthFlagSetBits flagSetBit) const
{
	VkFormatProperties formatProperties{};
	VkFormat format = TranslateDataFormatFourthSetToVKFormat(flagSetBit);

	vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &formatProperties);

	{
		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.fourthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.fourthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.fourthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.fourthSet |= flagSetBit;
	}

	{
		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.fourthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.fourthSet |= flagSetBit;
	}

	{
		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.fourthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.fourthSet |= flagSetBit;
	}
}

void PhysicalDeviceInternal::GetFifthSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& formatsSupportedFeatures, DataFormatFifthFlagSetBits flagSetBit) const
{
	VkFormatProperties formatProperties{};
	VkFormat format = TranslateDataFormatFifthSetToVKFormat(flagSetBit);

	vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &formatProperties);

	{
		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.fifthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.fifthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.fifthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.fifthSet |= flagSetBit;
	}

	{
		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.fifthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.fifthSet |= flagSetBit;
	}

	{
		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.fifthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.fifthSet |= flagSetBit;
	}
}

void PhysicalDeviceInternal::GetSixthSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& formatsSupportedFeatures, DataFormatSixthFlagSetBits flagSetBit) const
{
	VkFormatProperties formatProperties{};
	VkFormat format = TranslateDataFormatSixthSetToVKFormat(flagSetBit);

	vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &formatProperties);

	{
		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.sixthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.sixthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.sixthSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.sixthSet |= flagSetBit;
	}

	{
		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.sixthSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.sixthSet |= flagSetBit;
	}

	{
		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.sixthSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.sixthSet |= flagSetBit;
	}
}

void PhysicalDeviceInternal::GetSeventhSetsFormatsSupportedFeatures(FormatsSupportedFullFeatures& formatsSupportedFeatures, DataFormatSeventhFlagSetBits flagSetBit) const
{
	VkFormatProperties formatProperties{};
	VkFormat format = TranslateDataFormatSeventhSetToVKFormat(flagSetBit);

	vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &formatProperties);

	{
		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.seventhSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.seventhSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.seventhSet |= flagSetBit;

		if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
			formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.seventhSet |= flagSetBit;
	}

	{
		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.seventhSet |= flagSetBit;

		if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.seventhSet |= flagSetBit;
	}

	{
		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.seventhSet |= flagSetBit;

		if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
			formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.seventhSet |= flagSetBit;
	}
}
