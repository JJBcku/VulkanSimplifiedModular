export module VulkanSimplifiers.ImageDataList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.ImageDataList.Internal;
import VulkanSimplifiers.ImageDataList.Data;

import VulkanSimplifiers.Common.DataFormatFlags;
import VulkanSimplifiers.Common.ImageUsageFlags;

export class ImageDataListSimplifier
{
public:
	ImageDataListSimplifier(ImageDataListInternal& ref);
	~ImageDataListSimplifier();

	ImageDataListSimplifier& operator=(const ImageDataListSimplifier&) noexcept = delete;

	IDObject<AutoCleanup2DImage> AddSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity = 0, size_t addOnReserve = 0);
	IDObject<AutoCleanupMipMapped2DImage> AddMipMappedSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool calculateMipmapsFromBiggestSize,
		size_t initialImageViewListCapacity = 0, size_t addOnReserve = 0);

	bool RemoveSingleSampled2DImage(IDObject<AutoCleanup2DImage> imageID, bool throwOnIDNotFound = true);
	bool RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound = true);

private:
	ImageDataListInternal& _internal;
};