module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.ImageDataList.Internal;

ImageDataListInternal::ImageDataListInternal(const ImageDataCreationData& creationData, const LogicalDeviceCoreInternal& deviceCore, const DeviceRenderPassDataInternal& renderPassData,
	MemoryObjectsListInternal& memoryList, VkDevice device) : _deviceCore(deviceCore), _renderPassData(renderPassData), _memoryList(memoryList), _device(device),
	_singleSampled2DImage(creationData.singleSampled2DImageListInitialCapacity), _singleSampledMipMapped2DImage(creationData.singleSampledMipMapped2DListInitialCapacity),
	_framebuffersList(creationData.framebuffersListInitialCapacity)
{
}

ImageDataListInternal::~ImageDataListInternal()
{
}

IDObject<AutoCleanup2DSimpleImage> ImageDataListInternal::AddSimple2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
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

	return _singleSampled2DImage.AddObject(AutoCleanup2DSimpleImage(width, height, createInfo.format, _device, image, initialImageViewListCapacity), addOnReserve);
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

bool ImageDataListInternal::RemoveSimple2DImage(IDObject<AutoCleanup2DSimpleImage> imageID, bool throwOnIDNotFound)
{
	bool ret = _singleSampled2DImage.CheckForID(imageID);

	if (!ret && throwOnIDNotFound)
		throw std::runtime_error("ImageDataListInternal::RemoveSingleSampled2DImage Error: Program tried to delete a non-existent image!");

	if (ret)
	{
		auto& imageData = _singleSampled2DImage.GetObject(imageID);

		auto bindingData = imageData.GetBindingData();

		ret = _singleSampled2DImage.RemoveObject(imageID, true);

		if (bindingData.has_value())
			_memoryList.RemoveSuballocation(bindingData.value().first, bindingData.value().second, true);
	}

	return ret;
}

bool ImageDataListInternal::RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound)
{
	bool ret = _singleSampledMipMapped2DImage.CheckForID(imageID);

	if (!ret && throwOnIDNotFound)
		throw std::runtime_error("ImageDataListInternal::RemoveMipMappedSingleSampled2DImage Error: Program tried to delete a non-existent image!");

	if (ret)
	{
		auto& imageData = _singleSampledMipMapped2DImage.GetObject(imageID);

		auto bindingData = imageData.GetBindingData();

		ret = _singleSampledMipMapped2DImage.RemoveObject(imageID, true);

		if (bindingData.has_value())
			_memoryList.RemoveSuballocation(bindingData.value().first, bindingData.value().second, true);
	}

	return ret;
}

std::uint64_t ImageDataListInternal::GetImageRequiredAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetImageRequiredAligment();
}

std::uint64_t ImageDataListInternal::GetImageSize(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetImageSize();
}

std::uint32_t ImageDataListInternal::GetImageMemoryTypeMask(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetImageMemoryTypeMask();
}

std::pair<std::uint64_t, std::uint64_t> ImageDataListInternal::GetSizeAndAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetSizeAndAligment();
}

std::uint32_t ImageDataListInternal::GetImageWidth(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetWidth();
}

std::uint32_t ImageDataListInternal::GetImageHeight(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetHeight();
}

VkImage ImageDataListInternal::GetImage(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _singleSampled2DImage.GetConstObject(imageID).GetImage();
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

std::uint32_t ImageDataListInternal::GetImageWidth(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _singleSampledMipMapped2DImage.GetConstObject(imageID).GetWidth();
}

std::uint32_t ImageDataListInternal::GetImageHeight(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _singleSampledMipMapped2DImage.GetConstObject(imageID).GetHeight();
}

VkImage ImageDataListInternal::GetImage(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _singleSampledMipMapped2DImage.GetConstObject(imageID).GetImage();
}

void ImageDataListInternal::BindImage(IDObject<AutoCleanup2DSimpleImage> imageID, AllocationFullID allocationID, size_t addOnReserve)
{
	auto& imageData = _singleSampled2DImage.GetObject(imageID);

	VkImage image = imageData.GetImage();
	size_t size = imageData.GetImageSize();
	size_t aligment = imageData.GetImageRequiredAligment();

	auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserve);

	imageData.BindImage(allocationID, beggining);
}

void ImageDataListInternal::BindImage(IDObject<AutoCleanupMipMapped2DImage> imageID, AllocationFullID allocationID, size_t addOnReserve)
{
	auto& imageData = _singleSampledMipMapped2DImage.GetObject(imageID);

	VkImage image = imageData.GetImage();
	size_t size = imageData.GetImageSize();
	size_t aligment = imageData.GetImageRequiredAligment();

	auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserve);

	imageData.BindImage(allocationID, beggining);
}

IDObject<AutoCleanupImageView> ImageDataListInternal::AddImageView(IDObject<AutoCleanup2DSimpleImage> imageID, size_t addOnReserve)
{
	auto& imageData = _singleSampled2DImage.GetObject(imageID);

	return imageData.AddImageView(addOnReserve);
}

IDObject<AutoCleanupImageView> ImageDataListInternal::AddImageView(IDObject<AutoCleanupMipMapped2DImage> imageID, std::uint32_t baseMipLevel, std::uint32_t levelCount,
	size_t addOnReserve)
{
	auto& imageData = _singleSampledMipMapped2DImage.GetObject(imageID);

	return imageData.AddImageView(baseMipLevel, levelCount, addOnReserve);
}

VkImageView ImageDataListInternal::GetImageView(IDObject<AutoCleanup2DSimpleImage> imageID, IDObject<AutoCleanupImageView> viewID) const
{
	auto& imageData = _singleSampled2DImage.GetConstObject(imageID);

	return imageData.GetImageView(viewID);
}

VkImageView ImageDataListInternal::GetImageView(IDObject<AutoCleanupMipMapped2DImage> imageID, IDObject<AutoCleanupImageView> viewID) const
{
	auto& imageData = _singleSampledMipMapped2DImage.GetConstObject(imageID);

	return imageData.GetImageView(viewID);
}

IDObject<AutoCleanupFramebuffer> ImageDataListInternal::AddFramebuffer(IDObject<AutoCleanupRenderPass> renderPass,
	const std::vector<std::pair<ImageIDUnion, IDObject<AutoCleanupImageView>>>& attachmentsList, std::uint32_t width, std::uint32_t height, std::uint32_t layers,
	size_t addOnReserve)
{
	VkFramebufferCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	createInfo.renderPass = _renderPassData.GetRenderPass(renderPass);

	std::vector<VkImageView> imageViews;
	imageViews.reserve(attachmentsList.size());

	for (auto& attachmentData : attachmentsList)
	{
		auto& imageID = attachmentData.first;

		switch (imageID.type)
		{
		case ImageIDType::SIMPLE_2D:
			imageViews.push_back(GetImageView(imageID.simple2D.ID, attachmentData.second));
			break;
		case ImageIDType::MIPMAPPED_2D:
			imageViews.push_back(GetImageView(imageID.mipMapped2D.ID, attachmentData.second));
			break;
		case ImageIDType::UNKNOWN:
		default:
			throw std::runtime_error("ImageDataListInternal::AddFramebuffer Error: Program was given an erroneous value for a attachments image ID type!");
		}
	}

	createInfo.attachmentCount = static_cast<std::uint32_t>(imageViews.size());
	createInfo.pAttachments = imageViews.data();
	createInfo.width = width;
	createInfo.height = height;
	createInfo.layers = layers;

	VkFramebuffer add = VK_NULL_HANDLE;

	if (vkCreateFramebuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("ImageDataListInternal::AddFramebuffer Error: Program failed to create a framebuffer!");

	return _framebuffersList.AddObject(AutoCleanupFramebuffer(_device, add), addOnReserve);
}

bool ImageDataListInternal::RemoveFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound)
{
	return _framebuffersList.RemoveObject(framebufferID, throwOnIDNotFound);
}

VkFramebuffer ImageDataListInternal::GetFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID) const
{
	return _framebuffersList.GetConstObject(framebufferID).GetFramebuffer();
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
