module VulkanSimplifiers.ImageDataList;

ImageDataListSimplifier::ImageDataListSimplifier(ImageDataListInternal& ref) : _internal(ref)
{
}

ImageDataListSimplifier::~ImageDataListSimplifier()
{
}

IDObject<AutoCleanup2DImage> ImageDataListSimplifier::AddSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
	const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserve)
{
	return _internal.AddSingleSampled2DImage(width, height, format, usageFlags, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserve);
}

IDObject<AutoCleanupMipMapped2DImage> ImageDataListSimplifier::AddMipMappedSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format,
	ImageUsageFlags usageFlags, const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool calculateMipmapsFromBiggestSize,
	size_t initialImageViewListCapacity, size_t addOnReserve)
{
	return _internal.AddMipMappedSingleSampled2DImage(width, height, format, usageFlags, queuesUsingImage, preInitialized, calculateMipmapsFromBiggestSize,
		initialImageViewListCapacity, addOnReserve);
}

bool ImageDataListSimplifier::RemoveSingleSampled2DImage(IDObject<AutoCleanup2DImage> imageID, bool throwOnIDNotFound)
{
	return _internal.RemoveSingleSampled2DImage(imageID, throwOnIDNotFound);
}

bool ImageDataListSimplifier::RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound)
{
	return _internal.RemoveMipMappedSingleSampled2DImage(imageID, throwOnIDNotFound);
}

std::uint64_t ImageDataListSimplifier::GetImageRequiredAligment(IDObject<AutoCleanup2DImage> imageID) const
{
	return _internal.GetImageRequiredAligment(imageID);
}

std::uint64_t ImageDataListSimplifier::GetImageSize(IDObject<AutoCleanup2DImage> imageID) const
{
	return _internal.GetImageSize(imageID);
}

std::uint32_t ImageDataListSimplifier::GetImageMemoryTypeMask(IDObject<AutoCleanup2DImage> imageID) const
{
	return _internal.GetImageMemoryTypeMask(imageID);
}

std::pair<std::uint64_t, std::uint64_t> ImageDataListSimplifier::GetSizeAndAligment(IDObject<AutoCleanup2DImage> imageID) const
{
	return _internal.GetSizeAndAligment(imageID);
}

std::uint64_t ImageDataListSimplifier::GetImageRequiredAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _internal.GetImageRequiredAligment(imageID);
}

std::uint64_t ImageDataListSimplifier::GetImageSize(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _internal.GetImageSize(imageID);
}

std::uint32_t ImageDataListSimplifier::GetImageMemoryTypeMask(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _internal.GetImageMemoryTypeMask(imageID);
}

std::pair<std::uint64_t, std::uint64_t> ImageDataListSimplifier::GetSizeAndAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const
{
	return _internal.GetSizeAndAligment(imageID);
}
