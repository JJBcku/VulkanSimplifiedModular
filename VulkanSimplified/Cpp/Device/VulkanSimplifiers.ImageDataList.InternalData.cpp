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
}

AutoCleanupImage::~AutoCleanupImage()
{
	DestroyImage();
}

AutoCleanupImage::AutoCleanupImage(AutoCleanupImage&& rhs) noexcept : _device(rhs._device), _image(rhs._image), _imageViews(std::move(rhs._imageViews))
{
	rhs._device = VK_NULL_HANDLE;
	rhs._image = VK_NULL_HANDLE;
}

AutoCleanupImage& AutoCleanupImage::operator=(AutoCleanupImage&& rhs) noexcept
{
	DestroyImage();
	_device = rhs._device;
	_image = rhs._image;
	_imageViews = std::move(rhs._imageViews);

	rhs._device = VK_NULL_HANDLE;
	rhs._image = VK_NULL_HANDLE;
	return *this;
}

VkImage AutoCleanupImage::GetImage() const
{
	return _image;
}

VkImageView AutoCleanupImage::GetImageView(IDObject<AutoCleanupImageView> imageViewID) const
{
	return _imageViews.GetConstObject(imageViewID).GetImageView();
}

bool AutoCleanupImage::DeleteImageView(IDObject<AutoCleanupImageView> imageViewID, bool throwOnIDNotFound)
{
	return _imageViews.RemoveObject(imageViewID, throwOnIDNotFound);
}

void AutoCleanupImage::ResetImageViewList(size_t newImageViewListCapacity)
{
	_imageViews.Reset(newImageViewListCapacity);
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

AutoCleanupMipMapped2DImage::AutoCleanupMipMapped2DImage(std::uint32_t width, std::uint32_t height, std::uint32_t mipmapLevels, VkFormat format, VkDevice device, VkImage image,
	size_t initialImageViewListCapacity) : AutoCleanup2DImage(width, height, format, device, image, initialImageViewListCapacity), _mipmapLevels(mipmapLevels), _padding(0)
{
}

AutoCleanupMipMapped2DImage::~AutoCleanupMipMapped2DImage()
{
}
