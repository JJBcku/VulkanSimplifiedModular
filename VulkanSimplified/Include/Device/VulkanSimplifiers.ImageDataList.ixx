export module VulkanSimplifiers.ImageDataList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.ImageDataList.Internal;
import VulkanSimplifiers.ImageDataList.Data;

import VulkanSimplifiers.Common.DataFormatFlags;
import VulkanSimplifiers.Common.ImageUsageFlags;
import VulkanSimplifiers.MemoryObjectsList.Data;

export class ImageDataListSimplifier
{
public:
	ImageDataListSimplifier(ImageDataListInternal& ref);
	~ImageDataListSimplifier();

	ImageDataListSimplifier& operator=(const ImageDataListSimplifier&) noexcept = delete;

	IDObject<AutoCleanup2DSimpleImage> AddSimple2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity = 0, size_t addOnReserve = 0);
	IDObject<AutoCleanupMipMapped2DImage> AddMipMappedSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool calculateMipmapsFromBiggestSize,
		size_t initialImageViewListCapacity = 0, size_t addOnReserve = 0);

	bool RemoveSimple2DImage(IDObject<AutoCleanup2DSimpleImage> imageID, bool throwOnIDNotFound = true);
	bool RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound = true);

	std::uint64_t GetImageRequiredAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const;
	std::uint64_t GetImageSize(IDObject<AutoCleanup2DSimpleImage> imageID) const;
	std::uint32_t GetImageMemoryTypeMask(IDObject<AutoCleanup2DSimpleImage> imageID) const;

	std::pair<std::uint64_t, std::uint64_t> GetSizeAndAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const;

	std::uint64_t GetImageRequiredAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const;
	std::uint64_t GetImageSize(IDObject<AutoCleanupMipMapped2DImage> imageID) const;
	std::uint32_t GetImageMemoryTypeMask(IDObject<AutoCleanupMipMapped2DImage> imageID) const;

	std::pair<std::uint64_t, std::uint64_t> GetSizeAndAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const;

	void BindImage(IDObject<AutoCleanup2DSimpleImage> imageID, AllocationFullID allocationID, size_t addOnReserve = 0);
	void BindImage(IDObject<AutoCleanupMipMapped2DImage> imageID, AllocationFullID allocationID, size_t addOnReserve = 0);

	IDObject<AutoCleanupImageView> AddImageView(IDObject<AutoCleanup2DSimpleImage> imageID, size_t addOnReserve = 0);
	IDObject<AutoCleanupImageView> AddImageView(IDObject<AutoCleanupMipMapped2DImage> imageID, std::uint32_t baseMipLevel, std::uint32_t levelCount, size_t addOnReserve = 0);

private:
	ImageDataListInternal& _internal;
};