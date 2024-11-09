module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.ImageDataList.InternalData;

import std;
export import ListTemplates.UnsortedList;

export class AutoCleanupImageView
{
public:
	AutoCleanupImageView(VkDevice device, VkImageView imageView);
	~AutoCleanupImageView();

	AutoCleanupImageView(const AutoCleanupImageView&) noexcept = delete;
	AutoCleanupImageView(AutoCleanupImageView&& rhs) noexcept;

	AutoCleanupImageView& operator=(const AutoCleanupImageView&) noexcept = delete;
	AutoCleanupImageView& operator=(AutoCleanupImageView&& rhs) noexcept;

	VkImageView GetImageView() const;

private:
	VkDevice _device;
	VkImageView _imageView;

	void DestroyImageView();
};

export class AutoCleanupImage
{
public:
	VkImage GetImage() const;
	VkImageView GetImageView(IDObject<AutoCleanupImageView> imageViewID) const;

	bool DeleteImageView(IDObject<AutoCleanupImageView> imageViewID, bool throwOnIDNotFound);
	void ResetImageViewList(size_t newImageViewListCapacity);

	std::uint64_t GetImageRequiredAligment() const;
	std::uint64_t GetImageSize() const;
	std::uint32_t GetImageMemoryTypeMask() const;

	std::pair<std::uint64_t, std::uint64_t> GetSizeAndAligment() const;

protected:
	AutoCleanupImage(VkDevice device, VkImage image, VkFormat format, size_t initialImageViewListCapacity);
	~AutoCleanupImage();

	AutoCleanupImage(const AutoCleanupImage&) noexcept = delete;
	AutoCleanupImage(AutoCleanupImage&& rhs) noexcept;

	AutoCleanupImage& operator=(const AutoCleanupImage&) noexcept = delete;
	AutoCleanupImage& operator=(AutoCleanupImage&& rhs) noexcept;

private:
	VkDevice _device;
	VkImage _image;
	VkFormat _format;
	std::uint32_t _memoryTypeMask;

	std::uint64_t _size;
	std::uint64_t _aligment;

	UnsortedList<AutoCleanupImageView> _imageViews;

	void DestroyImage();
};

export class AutoCleanup2DImage : public AutoCleanupImage
{
public:
	AutoCleanup2DImage(std::uint32_t width, std::uint32_t height, VkFormat format, VkDevice device, VkImage image, size_t initialImageViewListCapacity);
	~AutoCleanup2DImage();

	AutoCleanup2DImage(const AutoCleanup2DImage&) noexcept = delete;
	AutoCleanup2DImage(AutoCleanup2DImage&& rhs) noexcept = default;

	AutoCleanup2DImage& operator=(const AutoCleanup2DImage&) noexcept = delete;
	AutoCleanup2DImage& operator=(AutoCleanup2DImage&& rhs) noexcept = default;
	
protected:
	std::uint32_t GetWidth() const;
	std::uint32_t GetHeight() const;

private:
	std::uint32_t _width;
	std::uint32_t _height;
};

export class AutoCleanupMipMapped2DImage : public AutoCleanup2DImage
{
public:
	AutoCleanupMipMapped2DImage(std::uint32_t width, std::uint32_t height, std::uint32_t mipmapLevels, VkFormat format, VkDevice device, VkImage image,
		size_t initialImageViewListCapacity);
	~AutoCleanupMipMapped2DImage();

	AutoCleanupMipMapped2DImage(const AutoCleanupMipMapped2DImage&) noexcept = delete;
	AutoCleanupMipMapped2DImage(AutoCleanupMipMapped2DImage&& rhs) noexcept = default;

	AutoCleanupMipMapped2DImage& operator=(const AutoCleanupMipMapped2DImage&) noexcept = delete;
	AutoCleanupMipMapped2DImage& operator=(AutoCleanupMipMapped2DImage&& rhs) noexcept = default;

private:
	std::uint32_t _mipmapLevels;
	std::uint32_t _padding;
};
