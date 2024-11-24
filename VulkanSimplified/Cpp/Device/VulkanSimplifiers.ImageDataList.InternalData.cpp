module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.ImageDataList.InternalData;

AutoCleanupImageView::AutoCleanupImageView(VkDevice device, VkImageView imageView) : _device(device), _imageView(imageView)
{
}

AutoCleanupImageView::~AutoCleanupImageView()
{
	DestroyImageView();
}

AutoCleanupImageView::AutoCleanupImageView(AutoCleanupImageView&& rhs) noexcept : _device(rhs._device), _imageView(rhs._imageView)
{
	rhs._device = VK_NULL_HANDLE;
	rhs._imageView = VK_NULL_HANDLE;
}

AutoCleanupImageView& AutoCleanupImageView::operator=(AutoCleanupImageView&& rhs) noexcept
{
	DestroyImageView();
	_device = rhs._device;
	_imageView = rhs._imageView;

	rhs._device = VK_NULL_HANDLE;
	rhs._imageView = VK_NULL_HANDLE;
	return *this;
}

VkImageView AutoCleanupImageView::GetImageView() const
{
	return _imageView;
}

void AutoCleanupImageView::DestroyImageView()
{
	if (_imageView != VK_NULL_HANDLE)
	{
		vkDestroyImageView(_device, _imageView, nullptr);
		_imageView = VK_NULL_HANDLE;
	}
}

AutoCleanupImage::AutoCleanupImage(VkDevice device, VkImage image, VkFormat format, size_t initialImageViewListCapacity) : _device(device),
_image(image), _format(format), _imageViews(initialImageViewListCapacity)
{
	VkMemoryRequirements req{};

	vkGetImageMemoryRequirements(_device, image, &req);

	_memoryTypeMask = req.memoryTypeBits;
	_size = req.size;
	_aligment = req.alignment;
}

AutoCleanupImage::~AutoCleanupImage()
{
	DestroyImage();
}

AutoCleanupImage::AutoCleanupImage(AutoCleanupImage&& rhs) noexcept : _device(rhs._device), _image(rhs._image), _format(rhs._format), _memoryTypeMask(rhs._memoryTypeMask),
	_size(rhs._size), _aligment(rhs._aligment), _bindingData(std::move(rhs._bindingData)), _imageViews(std::move(rhs._imageViews))
{
	rhs._device = VK_NULL_HANDLE;
	rhs._image = VK_NULL_HANDLE;
	rhs._format = VK_FORMAT_UNDEFINED;
	rhs._memoryTypeMask = 0;
	rhs._size = 0;
	rhs._aligment = std::numeric_limits<std::uint64_t>::max();
}

AutoCleanupImage& AutoCleanupImage::operator=(AutoCleanupImage&& rhs) noexcept
{
	DestroyImage();
	_device = rhs._device;
	_image = rhs._image;
	_format = rhs._format;
	_memoryTypeMask = rhs._memoryTypeMask;
	_size = rhs._size;
	_aligment = rhs._aligment;
	_bindingData = std::move(rhs._bindingData);
	_imageViews = std::move(rhs._imageViews);

	rhs._device = VK_NULL_HANDLE;
	rhs._image = VK_NULL_HANDLE;
	rhs._format = VK_FORMAT_UNDEFINED;
	rhs._memoryTypeMask = 0;
	rhs._size = 0;
	rhs._aligment = std::numeric_limits<std::uint64_t>::max();
	return *this;
}

IDObject<AutoCleanupImageView> AutoCleanupImage::AddImageView(VkComponentMapping componentMapping, VkImageSubresourceRange subresourceRange, VkImageViewType viewType,
	size_t addOnReserve)
{
	VkImageViewCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	createInfo.image = _image;
	createInfo.viewType = viewType;
	createInfo.format = _format;
	createInfo.components = componentMapping;
	createInfo.subresourceRange = subresourceRange;

	VkImageView add = VK_NULL_HANDLE;

	if (vkCreateImageView(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("AutoCleanupImage::AddImageView Error: Program failed to create an image view!");

	return _imageViews.AddObject(AutoCleanupImageView(_device, add), addOnReserve);
}

VkImage AutoCleanupImage::GetImage() const
{
	return _image;
}

VkImageView AutoCleanupImage::GetImageView(IDObject<AutoCleanupImageView> imageViewID) const
{
	return _imageViews.GetConstObject(imageViewID).GetImageView();
}

std::optional<ImageBindingData> AutoCleanupImage::GetBindingData() const
{
	return _bindingData;
}

bool AutoCleanupImage::DeleteImageView(IDObject<AutoCleanupImageView> imageViewID, bool throwOnIDNotFound)
{
	return _imageViews.RemoveObject(imageViewID, throwOnIDNotFound);
}

void AutoCleanupImage::ResetImageViewList(size_t newImageViewListCapacity)
{
	_imageViews.Reset(newImageViewListCapacity);
}

std::uint64_t AutoCleanupImage::GetImageRequiredAligment() const
{
	return _aligment;
}

std::uint64_t AutoCleanupImage::GetImageSize() const
{
	return _size;
}

std::uint32_t AutoCleanupImage::GetImageMemoryTypeMask() const
{
	return _memoryTypeMask;
}

std::pair<std::uint64_t, std::uint64_t> AutoCleanupImage::GetSizeAndAligment() const
{
	return std::pair<std::uint64_t, std::uint64_t>(_size, _aligment);
}

void AutoCleanupImage::BindImage(AllocationFullID allocationID, size_t bindingBeggining)
{
	if (_bindingData.has_value())
		throw std::runtime_error("AutoCleanupImage::BindImage Error: Program tried to bind an already bound image!");

	_bindingData.emplace(allocationID, bindingBeggining);
}

void AutoCleanupImage::DestroyImage()
{
	if (_imageViews.GetUsedSize() > 0)
		ResetImageViewList(0);

	if (_image != VK_NULL_HANDLE)
	{
		vkDestroyImage(_device, _image, nullptr);
		_image = VK_NULL_HANDLE;
	}
}

AutoCleanup2DImage::AutoCleanup2DImage(std::uint32_t width, std::uint32_t height, VkFormat format, VkDevice device, VkImage image,
	size_t initialImageViewListCapacity) : AutoCleanupImage(device, image, format, initialImageViewListCapacity), _width(width), _height(height)
{
}

AutoCleanup2DImage::~AutoCleanup2DImage()
{
}

std::uint32_t AutoCleanup2DImage::GetWidth() const
{
	return _width;
}

std::uint32_t AutoCleanup2DImage::GetHeight() const
{
	return _height;
}

AutoCleanup2DSimpleImage::AutoCleanup2DSimpleImage(std::uint32_t width, std::uint32_t height, VkFormat format, VkDevice device, VkImage image, size_t initialImageViewListCapacity) : 
	AutoCleanup2DImage(width, height, format, device, image, initialImageViewListCapacity)
{
}

AutoCleanup2DSimpleImage::~AutoCleanup2DSimpleImage()
{
}

IDObject<AutoCleanupImageView> AutoCleanup2DSimpleImage::AddImageView(size_t addOnReserve)
{
	VkImageSubresourceRange range{};
	range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	range.baseMipLevel = 0;
	range.levelCount = 1;
	range.baseArrayLayer = 0;
	range.layerCount = 1;

	return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserve);
}

AutoCleanupMipMapped2DImage::AutoCleanupMipMapped2DImage(std::uint32_t width, std::uint32_t height, std::uint32_t mipmapLevels, VkFormat format, VkDevice device, VkImage image,
	size_t initialImageViewListCapacity) : AutoCleanup2DImage(width, height, format, device, image, initialImageViewListCapacity), _mipmapLevels(mipmapLevels), _padding(0)
{
}

AutoCleanupMipMapped2DImage::~AutoCleanupMipMapped2DImage()
{
}

IDObject<AutoCleanupImageView> AutoCleanupMipMapped2DImage::AddImageView(std::uint32_t baseMipLevel, std::uint32_t levelCount, size_t addOnReserve)
{
	if (baseMipLevel >= _mipmapLevels)
		throw std::runtime_error("AutoCleanupMipMapped2DImage::AddImageView Error: Program was given a base mipmap level bigger than level amount!");

	if (levelCount >= _mipmapLevels)
		throw std::runtime_error("AutoCleanupMipMapped2DImage::AddImageView Error: Program was given a viewed mipmap levels count bigger than level amount!");

	std::uint32_t maxLevel = baseMipLevel + levelCount;

	if (maxLevel > levelCount)
		throw std::runtime_error("AutoCleanupMipMapped2DImage::AddImageView Error: Maximum used level calculations overflowed!");

	if (maxLevel > _mipmapLevels)
		throw std::runtime_error("AutoCleanupMipMapped2DImage::AddImageView Error: Program was given a maximum mipmap level bigger than level amount!");

	VkImageSubresourceRange range{};
	range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	range.baseMipLevel = baseMipLevel;
	range.levelCount = levelCount;
	range.baseArrayLayer = 0;
	range.layerCount = 1;

	return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserve);
}
