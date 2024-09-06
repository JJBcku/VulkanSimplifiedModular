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
