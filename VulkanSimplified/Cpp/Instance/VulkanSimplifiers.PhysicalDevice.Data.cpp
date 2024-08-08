module VulkanSimplifiers.PhysicalDevice.Data;

Vulkan10MaxImageSizeLimits::Vulkan10MaxImageSizeLimits()
{
	maxImageDimension1D = 0;
	maxImageDimension2D = 0;
	maxImageDimension3D = 0;
	maxImageArrayLayers = 0;
}

Vulkan10DescriptorSetBindingLimits::Vulkan10DescriptorSetBindingLimits()
{
	maxBoundDescriptorSets = 0;
	maxPerStageDescriptorSamplers = 0;
	maxPerStageDescriptorUniformBuffers = 0;
	maxPerStageDescriptorStorageBuffers = 0;
	maxPerStageDescriptorSampledImages = 0;
	maxPerStageDescriptorStorageImages = 0;
	maxPerStageDescriptorInputAttachments = 0;
	maxPerStageResources = 0;
}

Vulkan10DescriptorSetLimits::Vulkan10DescriptorSetLimits()
{
	maxDescriptorSetSamplers = 0;
	maxDescriptorSetUniformBuffers = 0;
	maxDescriptorSetUniformBuffersDynamic = 0;
	maxDescriptorSetStorageBuffers = 0;
	maxDescriptorSetStorageBuffersDynamic = 0;
	maxDescriptorSetSampledImages = 0;
	maxDescriptorSetStorageImages = 0;
	maxDescriptorSetInputAttachments = 0;
}

Vulkan10VertexShaderLimits::Vulkan10VertexShaderLimits()
{
	maxVertexInputAttributes = 0;
	maxVertexInputBindings = 0;
	maxVertexInputAttributeOffset = 0;
	maxVertexInputBindingStride = 0;
	maxVertexOutputComponents = 0;
}

Vulkan10FragmentShaderLimits::Vulkan10FragmentShaderLimits()
{
	maxFragmentInputComponents = 0;
	maxFragmentOutputAttachments = 0;
	maxFragmentDualSrcAttachments = 0;
	maxFragmentCombinedOutputResources = 0;
}

Vulkan10ViewportLimits::Vulkan10ViewportLimits()
{
	maxViewports = 0;
	maxViewportDimensionsX = 0;
	maxViewportDimensionsY = 0;
	viewportBoundsRangeMin = 0.0;
	viewportBoundsRangeMax = 0.0;
	viewportSubPixelBits = 0;
}

Vulkan10FramebufferLimits::Vulkan10FramebufferLimits()
{
	maxFramebufferWidth = 0;
	maxFramebufferHeight = 0;
	maxFramebufferLayers = 0;
	framebufferColorSampleCounts = 0;
	framebufferDepthSampleCounts = 0;
	framebufferStencilSampleCounts = 0;
	framebufferNoAttachmentsSampleCounts = 0;
}

Vulkan10SamplingLimits::Vulkan10SamplingLimits()
{
	sampledImageColorSampleCounts = 0;
	sampledImageIntegerSampleCounts = 0;
	sampledImageDepthSampleCounts = 0;
	sampledImageStencilSampleCounts = 0;
	storageImageSampleCounts = 0;
}

Vulkan10DeviceLimits::Vulkan10DeviceLimits()
{
	maxUniformBufferRange = 0;
	maxStorageBufferRange = 0;
	maxPushConstantsSize = 0;

	maxMemoryAllocationCount = 0;
	maxSamplerAllocationCount = 0;

	subPixelPrecisionBits = 0;
	mipmapPrecisionBits = 0;

	maxDrawIndexedIndexValue = 0;

	maxSamplerLodBias = 0.0;
	maxSamplerAnisotropy = 0.0;

	maxColorAttachments = 0;
}

QueueFamily::QueueFamily()
{
	queueTypes = 0;
	queueCount = 0;
	timespampValidBits = 0;
	minImageTransferGranularityWidth = 0;
	minImageTransferGranularityHeight = 0;
	minImageTransferGranularityDepth = 0;
}

DeviceExtensionLists::DeviceExtensionLists()
{
	khrExtensions = 0;
}

DeviceVulkanPropertiesSimplified::DeviceVulkanPropertiesSimplified()
{
	apiMaxSupportedVersion = 0;
	driverVersion = 0;
	vendorID = 0;
	deviceID = 0;
	deviceType = DeviceType::OTHER;

	for (size_t i = 0; i < pipelineCacheID.size(); i++)
		pipelineCacheID[i] = 0;
}

SurfaceSupportData::SurfaceSupportData()
{
	minImageCount = 0;
	maxImageCount = 0;

	surfaceUsageFlags = 0;
	surfacePresentModes = 0;
}
