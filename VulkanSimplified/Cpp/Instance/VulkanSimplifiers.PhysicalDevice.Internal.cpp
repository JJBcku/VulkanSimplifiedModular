	module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.PhysicalDevice.Internal;

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
					if (formatData.format == VK_FORMAT_A1R5G5B5_UNORM_PACK16)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_A_1BIT_RGB_5BIT_UNORM_PACK16BIT;

					if (formatData.format == VK_FORMAT_A2B10G10R10_UNORM_PACK32)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_A_2BIT_BGR_10BIT_UNORM_PACK32BIT;

					if (formatData.format == VK_FORMAT_A2R10G10B10_UNORM_PACK32)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_A_2BIT_RGB_10BIT_UNORM_PACK32BIT;

					if (formatData.format == VK_FORMAT_A8B8G8R8_SNORM_PACK32)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_ABGR_8BIT_SNORM_PACK32BIT;

					if (formatData.format == VK_FORMAT_A8B8G8R8_SRGB_PACK32)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_ABGR_8BIT_SRGB_PACK32BIT;

					if (formatData.format == VK_FORMAT_A8B8G8R8_UNORM_PACK32)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_ABGR_8BIT_UNORM_PACK32BIT;

					if (formatData.format == VK_FORMAT_B10G11R11_UFLOAT_PACK32)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_B_10BIT_GR_11BIT_UFLOAT_PACK32BIT;

					if (formatData.format == VK_FORMAT_B4G4R4A4_UNORM_PACK16)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_BGRA_4BIT_UNORM_PACK16BIT;

					if (formatData.format == VK_FORMAT_B5G5R5A1_UNORM_PACK16)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_BGR_5BIT_A_1BIT_UNORM_PACK16BIT;

					if (formatData.format == VK_FORMAT_B5G6R5_UNORM_PACK16)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_B_5BIT_G_6BIT_R_5BIT_UNORM_PACK16BIT;

					if (formatData.format == VK_FORMAT_B8G8R8A8_SNORM)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_BGRA_8BIT_SNORM;

					if (formatData.format == VK_FORMAT_B8G8R8A8_SRGB)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_BGRA_8BIT_SRGB;

					if (formatData.format == VK_FORMAT_B8G8R8A8_UNORM)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_BGRA_8BIT_UNORM;

					if (formatData.format == VK_FORMAT_R16G16B16A16_SFLOAT)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGBA_16BIT_SFLOAT;

					if (formatData.format == VK_FORMAT_R16G16B16A16_SNORM)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGBA_16BIT_SNORM;

					if (formatData.format == VK_FORMAT_B8G8R8A8_UNORM)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGBA_16BIT_UNORM;

					if (formatData.format == VK_FORMAT_R4G4B4A4_UNORM_PACK16)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGBA_4BIT_UNORM_PACK16BIT;

					if (formatData.format == VK_FORMAT_R5G5B5A1_UNORM_PACK16)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGB_5BIT_A_1BIT_UNORM_PACK16BIT;

					if (formatData.format == VK_FORMAT_R5G6B5_UNORM_PACK16)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_R_5BIT_G_6BIT_B_5BIT_UNORM_PACK16BIT;

					if (formatData.format == VK_FORMAT_R8_UNORM)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_R_8BIT_UNORM;

					if (formatData.format == VK_FORMAT_R8G8B8A8_SNORM)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGBA_8BIT_SNORM;

					if (formatData.format == VK_FORMAT_R8G8B8A8_SRGB)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGBA_8BIT_SRGB;

					if (formatData.format == VK_FORMAT_R8G8B8A8_UNORM)
						ret.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace |= IMAGE_FORMAT_RGBA_8BIT_UNORM;
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
