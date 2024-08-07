export module VulkanSimplifiers.PhysicalDevice.Data;

import std;

export struct Vulkan10MaxImageSizeLimits
{
	std::uint64_t maxImageDimension1D;
	std::uint64_t maxImageDimension2D;
	std::uint64_t maxImageDimension3D;
	std::uint64_t maxImageArrayLayers;

	Vulkan10MaxImageSizeLimits();
};

export struct Vulkan10DescriptorSetBindingLimits
{
	std::uint64_t maxBoundDescriptorSets;
	std::uint64_t maxPerStageDescriptorSamplers;
	std::uint64_t maxPerStageDescriptorUniformBuffers;
	std::uint64_t maxPerStageDescriptorStorageBuffers;
	std::uint64_t maxPerStageDescriptorSampledImages;
	std::uint64_t maxPerStageDescriptorStorageImages;
	std::uint64_t maxPerStageDescriptorInputAttachments;
	std::uint64_t maxPerStageResources;

	Vulkan10DescriptorSetBindingLimits();
};

export struct Vulkan10DescriptorSetLimits
{
	Vulkan10DescriptorSetBindingLimits descriptorSetBindingsLimit;

	std::uint64_t maxDescriptorSetSamplers;
	std::uint64_t maxDescriptorSetUniformBuffers;
	std::uint64_t maxDescriptorSetUniformBuffersDynamic;
	std::uint64_t maxDescriptorSetStorageBuffers;
	std::uint64_t maxDescriptorSetStorageBuffersDynamic;
	std::uint64_t maxDescriptorSetSampledImages;
	std::uint64_t maxDescriptorSetStorageImages;
	std::uint64_t maxDescriptorSetInputAttachments;

	Vulkan10DescriptorSetLimits();
};

export struct Vulkan10VertexShaderLimits
{
	std::uint64_t maxVertexInputAttributes;
	std::uint64_t maxVertexInputBindings;
	std::uint64_t maxVertexInputAttributeOffset;
	std::uint64_t maxVertexInputBindingStride;
	std::uint64_t maxVertexOutputComponents;

	Vulkan10VertexShaderLimits();
};

export struct Vulkan10FragmentShaderLimits
{
	std::uint64_t maxFragmentInputComponents;
	std::uint64_t maxFragmentOutputAttachments;
	std::uint64_t maxFragmentDualSrcAttachments;
	std::uint64_t maxFragmentCombinedOutputResources;

	Vulkan10FragmentShaderLimits();
};

export struct Vulkan10ViewportLimits
{
	std::uint64_t maxViewports;
	std::uint64_t maxViewportDimensionsX;
	std::uint64_t maxViewportDimensionsY;
	double viewportBoundsRangeMin;
	double viewportBoundsRangeMax;
	std::uint64_t viewportSubPixelBits;

	Vulkan10ViewportLimits();
};

export struct Vulkan10FramebufferLimits
{
	std::uint64_t maxFramebufferWidth;
	std::uint64_t maxFramebufferHeight;
	std::uint64_t maxFramebufferLayers;
	std::uint64_t framebufferColorSampleCounts;
	std::uint64_t framebufferDepthSampleCounts;
	std::uint64_t framebufferStencilSampleCounts;
	std::uint64_t framebufferNoAttachmentsSampleCounts;

	Vulkan10FramebufferLimits();
};

export struct Vulkan10SamplingLimits
{
	std::uint64_t sampledImageColorSampleCounts;
	std::uint64_t sampledImageIntegerSampleCounts;
	std::uint64_t sampledImageDepthSampleCounts;
	std::uint64_t sampledImageStencilSampleCounts;
	std::uint64_t storageImageSampleCounts;

	Vulkan10SamplingLimits();
};

export struct Vulkan10DeviceLimits
{
	Vulkan10MaxImageSizeLimits maxImageSizes;

	std::uint64_t maxUniformBufferRange;
	std::uint64_t maxStorageBufferRange;
	std::uint64_t maxPushConstantsSize;

	std::uint64_t maxMemoryAllocationCount;
	std::uint64_t maxSamplerAllocationCount;

	Vulkan10DescriptorSetLimits descriptorSetLimits;

	Vulkan10VertexShaderLimits vertexShaderLimit;
	Vulkan10FragmentShaderLimits fragmentShaderLimit;

	std::uint64_t subPixelPrecisionBits;
	std::uint64_t mipmapPrecisionBits;

	std::uint64_t maxDrawIndexedIndexValue;

	double maxSamplerLodBias;
	double maxSamplerAnisotropy;

	Vulkan10ViewportLimits viewportLimits;
	Vulkan10FramebufferLimits framebufferLimits;

	std::uint64_t maxColorAttachments;

	Vulkan10SamplingLimits samplingLimits;

	Vulkan10DeviceLimits();
};

export enum class DeviceType : std::uint64_t
{
	OTHER,
	INTERGRATED_GPU,
	DISCRETE_GPU,
	VIRTUAL_GPU,
	CPU,
};

export typedef std::uint32_t QueueTypeFlags;

export enum QueueTypeFlagBits : QueueTypeFlags
{
	QUEUE_TYPE_GRAPHICS = 0x1,
	QUEUE_TYPE_COMPUTE = 0x2,
	QUEUE_TYPE_TRANSFER = 0x4,
	QUEUE_TYPE_SPARSE_BINDING = 0x8,
	QUEUE_TYPE_PROTECTED = 0x10,
	QUEUE_TYPE_VIDEO_DECODE = 0x20,
	QUEUE_TYPE_VIDEO_ENCODE = 0x40,
	QUEUE_TYPE_OPTICAL_FLOW = 0x100,
};

struct QueueFamily
{
	QueueTypeFlags queueTypes;
	std::uint32_t queueCount;
	std::uint32_t timespampValidBits;
	std::uint32_t minImageTransferGranularityWidth;
	std::uint32_t minImageTransferGranularityHeight;
	std::uint32_t minImageTransferGranularityDepth;

	QueueFamily();
};

export struct DeviceVulkanPropertiesSimplified
{
	std::uint32_t apiMaxSupportedVersion;
	std::uint32_t driverVersion;
	std::uint32_t vendorID;
	std::uint32_t deviceID;
	DeviceType deviceType;
	std::string deviceName;
	std::array<std::uint8_t, 16> pipelineCacheID;

	std::vector<QueueFamily> queueFamilies;

	Vulkan10DeviceLimits device10Limits;

	DeviceVulkanPropertiesSimplified();
};

export typedef std::uint64_t VulkanDeviceFeatureFlags;

export enum Vulkan10DeviceFeaturesFlagBits : VulkanDeviceFeatureFlags
{
	VULKAN10_DEVICE_FEATURE_FULL_DRAW_INDEX_UINT32 = 0x1,
	VULKAN10_DEVICE_FEATURE_INDEPENDENT_BLEND = 0x2,
	VULKAN10_DEVICE_FEATURE_FILL_MODE_NONSOLID = 0x4,
	VULKAN10_DEVICE_FEATURE_MULTI_VIEWPORT = 0x8,
	VULKAN10_DEVICE_FEATURE_SAMPLER_ANISOTROPY = 0x10,
	VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ETC2 = 0x20,
	VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR = 0x40,
	VULKAN10_DEVICE_FEATURE_TEXTURE_COMPRESSION_BC = 0x80,
	VULKAN10_DEVICE_FEATURE_SHADER_FLOAT64 = 0x100,
	VULKAN10_DEVICE_FEATURE_SHADER_INT64 = 0x200,
	VULKAN10_DEVICE_FEATURE_SHADER_INT16 = 0x400,
	VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_RESIDENCY = 0x800,
	VULKAN10_DEVICE_FEATURE_SHADER_RESOURCE_MINIMUM_LOD = 0x1000,
	VULKAN10_DEVICE_FEATURE_SPARSE_BINDING = 0x2000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_BUFFER = 0x4000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE2D = 0x8000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_IMAGE3D = 0x10000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_2_SAMPLES = 0x20000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_4_SAMPLES = 0x40000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_8_SAMPLES = 0x80000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_16_SAMPLES = 0x100000,
	VULKAN10_DEVICE_FEATURE_SPARSE_RESIDENCY_ALIASED = 0x200000,
	VULKAN10_DEVICE_FEATURE_VARIABLE_MULTISAMPLE_RATE = 0x400000,
	VULKAN10_DEVICE_FEATURE_INHERITED_QUERIES = 0x800000,
};

export enum Vulkan11DeviceFeaturesFlagBits : VulkanDeviceFeatureFlags
{
	VULKAN11_DEVICE_FEATURE_STORAGE_BUFFER_16BIT_ACCESS = 0x1,
	VULKAN11_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_16BIT_ACCESS = 0x2,
	VULKAN11_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_16BIT = 0x4,
	VULKAN11_DEVICE_FEATURE_STORAGE_INPUT_OUTPUT_16BIT = 0x8,
	VULKAN11_DEVICE_FEATURE_MULTIVIEW = 0x10,
};

export enum Vulkan12DeviceFeaturesFlagBits : VulkanDeviceFeatureFlags
{
	VULKAN12_DEVICE_FEATURE_STORAGE_BUFFER_8BIT_ACCESS = 0x1,
	VULKAN12_DEVICE_FEATURE_UNIFORM_AND_STORAGE_BUFFER_8BIT_ACCESS = 0x2,
	VULKAN12_DEVICE_FEATURE_STORAGE_PUSH_CONSTANT_8BIT = 0x4,
	VULKAN12_DEVICE_FEATURE_SHADER_BUFFER_INT64_ATOMICS = 0x8,
	VULKAN12_DEVICE_FEATURE_SHADER_SHARED_INT64_ATOMICS = 0x10,
	VULKAN12_DEVICE_FEATURE_SHADER_FLOAT_16BIT = 0x20,
	VULKAN12_DEVICE_FEATURE_SHADER_INT_8BIT = 0x40,
	VULKAN12_DEVICE_FEATURE_SCALAR_BLOCK_LAYOUT = 0x80,
};

export enum Vulkan13DeviceFeaturesFlagBits : VulkanDeviceFeatureFlags
{
	VULKAN13_DEVICE_FEATURE_SYNCHRONIZATION2 = 0X1,
	VULKAN13_DEVICE_FEATURE_TEXTURE_COMPRESSION_ASTC_HDR = 0X2,
	VULKAN13_DEVICE_FEATURE_MAINTENANCE4 = 0X4,
};

export struct SurfaceSupportData
{
	std::vector<bool> queuePresentingSupport;

	SurfaceSupportData();
};