module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.ImageDataList.Internal;

ImageDataListInternal::ImageDataListInternal(const ImageDataCreationData& creationData, const LogicalDeviceCoreInternal& deviceCore, VkDevice device) : _deviceCore(deviceCore),
	_device(device), _singleSampled2DImage(creationData.singleSampled2DImageListInitialCapacity),
	_singleSampledMipMapped2DImage(creationData.singleSampledMipMapped2DListInitialCapacity)
{
}

ImageDataListInternal::~ImageDataListInternal()
{
}

IDObject<AutoCleanup2DImage> ImageDataListInternal::AddSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
	const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserve)
{
	VkImage image = VK_NULL_HANDLE;
	VkImageCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

	createInfo.imageType = VK_IMAGE_TYPE_2D;
	createInfo.format = TranslateDataFormatToVkFormat(format);

	createInfo.extent.width = width;
	createInfo.extent.height = height;
	createInfo.extent.depth = 1;

	createInfo.mipLevels = 1;
	createInfo.arrayLayers = 1;
	createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

	createInfo.usage = TranslateImageUsage(usageFlags);

	std::vector<uint32_t> queueFamilies;

	if (queuesUsingImage.size() > 1)
	{
		queueFamilies = _deviceCore.GetQueueFamilies(queuesUsingImage);

		createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(queueFamilies.size());
		createInfo.pQueueFamilyIndices = queueFamilies.data();
	}
	else
	{
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	if (preInitialized)
		createInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
	else
		createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	if (vkCreateImage(_device, &createInfo, nullptr, &image) != VK_SUCCESS)
		throw std::runtime_error("ImageDataListInternal::AddSingleSampled2DImage Error: Program failed to create a single sampled, no mip maps, 2D image!");

	return _singleSampled2DImage.AddObject(AutoCleanup2DImage(width, height, createInfo.format, _device, image, initialImageViewListCapacity), addOnReserve);
}

IDObject<AutoCleanupMipMapped2DImage> ImageDataListInternal::AddMipMappedSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format,
	ImageUsageFlags usageFlags, const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool calculateMipmapsFromBiggestSize,
	size_t initialImageViewListCapacity, size_t addOnReserve)
{
	VkImage image = VK_NULL_HANDLE;
	VkImageCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

	createInfo.imageType = VK_IMAGE_TYPE_2D;
	createInfo.format = TranslateDataFormatToVkFormat(format);

	createInfo.extent.width = width;
	createInfo.extent.height = height;
	createInfo.extent.depth = 1;

	if (calculateMipmapsFromBiggestSize)
		createInfo.mipLevels = CalculateMipmapLevelsFromBiggest2D(width, height);
	else
		createInfo.mipLevels = CalculateMipmapLevelsFromSmallest2D(width, height);

	createInfo.arrayLayers = 1;
	createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

	createInfo.usage = TranslateImageUsage(usageFlags);

	std::vector<uint32_t> queueFamilies;

	if (queuesUsingImage.size() > 1)
	{
		queueFamilies = _deviceCore.GetQueueFamilies(queuesUsingImage);

		createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(queueFamilies.size());
		createInfo.pQueueFamilyIndices = queueFamilies.data();
	}
	else
	{
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	if (preInitialized)
		createInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
	else
		createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	if (vkCreateImage(_device, &createInfo, nullptr, &image) != VK_SUCCESS)
		throw std::runtime_error("ImageDataListInternal::AddMipMappedSingleSampled2DImage Error: Program failed to create a single sampled, mip mapped, 2D image!");

	return _singleSampledMipMapped2DImage.AddObject(AutoCleanupMipMapped2DImage(width, height, createInfo.mipLevels, createInfo.format, _device, image, initialImageViewListCapacity),
		addOnReserve);
}

bool ImageDataListInternal::RemoveSingleSampled2DImage(IDObject<AutoCleanup2DImage> imageID, bool throwOnIDNotFound)
{
	return _singleSampled2DImage.RemoveObject(imageID, throwOnIDNotFound);
}

bool ImageDataListInternal::RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound)
{
	return _singleSampledMipMapped2DImage.RemoveObject(imageID, throwOnIDNotFound);
}

std::uint64_t ImageDataListInternal::GetImageRequiredAligment(IDObject<AutoCleanup2DImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetImageRequiredAligment();
}

std::uint64_t ImageDataListInternal::GetImageSize(IDObject<AutoCleanup2DImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetImageSize();
}

std::uint32_t ImageDataListInternal::GetImageMemoryTypeMask(IDObject<AutoCleanup2DImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetImageMemoryTypeMask();
}

std::pair<std::uint64_t, std::uint64_t> ImageDataListInternal::GetSizeAndAligment(IDObject<AutoCleanup2DImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetSizeAndAligment();
}

std::uint64_t ImageDataListInternal::GetImageRequiredAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _singleSampledMipMapped2DImage.GetConstObject(imageID).GetImageRequiredAligment();
}

std::uint64_t ImageDataListInternal::GetImageSize(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _singleSampledMipMapped2DImage.GetConstObject(imageID).GetImageSize();
}

std::uint32_t ImageDataListInternal::GetImageMemoryTypeMask(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _singleSampledMipMapped2DImage.GetConstObject(imageID).GetImageMemoryTypeMask();
}

std::pair<std::uint64_t, std::uint64_t> ImageDataListInternal::GetSizeAndAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _singleSampledMipMapped2DImage.GetConstObject(imageID).GetSizeAndAligment();
}

std::uint32_t ImageDataListInternal::CalculateMipmapLevelsFromBiggest3D(std::uint32_t width, std::uint32_t height, std::uint32_t depth) const
{
	std::uint32_t ret = 0;

	std::uint32_t biggest = std::max(width, std::max(height, depth));

	while (biggest > 0)
	{
		ret++;
		biggest = biggest >> 1;
	}

	return ret;
}

std::uint32_t ImageDataListInternal::CalculateMipmapLevelsFromBiggest2D(std::uint32_t width, std::uint32_t height) const
{
	std::uint32_t ret = 0;

	std::uint32_t biggest = std::max(width, height);

	while (biggest > 0)
	{
		ret++;
		biggest = biggest >> 1;
	}

	return ret;
}

std::uint32_t ImageDataListInternal::CalculateMipmapLevelsFromSmallest3D(std::uint32_t width, std::uint32_t height, std::uint32_t depth) const
{
	std::uint32_t ret = 0;

	std::uint32_t smallest = std::min(width, std::min(height, depth));

	while (smallest > 0)
	{
		ret++;
		smallest = smallest >> 1;
	}

	return ret;
}

std::uint32_t ImageDataListInternal::CalculateMipmapLevelsFromSmallest2D(std::uint32_t width, std::uint32_t height) const
{
	std::uint32_t ret = 0;

	std::uint32_t smallest = std::min(width, height);

	while (smallest > 0)
	{
		ret++;
		smallest = smallest >> 1;
	}

	return ret;
}
