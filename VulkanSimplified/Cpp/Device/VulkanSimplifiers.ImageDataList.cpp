module VulkanSimplifiers.ImageDataList;

ImageDataListSimplifier::ImageDataListSimplifier(ImageDataListInternal& ref) : _internal(ref)
{
}

ImageDataListSimplifier::~ImageDataListSimplifier()
{
}

IDObject<AutoCleanup2DSimpleImage> ImageDataListSimplifier::AddSimple2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
	const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserve)
{
	return _internal.AddSimple2DImage(width, height, format, usageFlags, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserve);
}

IDObject<AutoCleanupMipMapped2DImage> ImageDataListSimplifier::AddMipMappedSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format,
	ImageUsageFlags usageFlags, const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool calculateMipmapsFromBiggestSize,
	size_t initialImageViewListCapacity, size_t addOnReserve)
{
	return _internal.AddMipMappedSingleSampled2DImage(width, height, format, usageFlags, queuesUsingImage, preInitialized, calculateMipmapsFromBiggestSize,
		initialImageViewListCapacity, addOnReserve);
}

bool ImageDataListSimplifier::RemoveSimple2DImage(IDObject<AutoCleanup2DSimpleImage> imageID, bool throwOnIDNotFound)
{
	return _internal.RemoveSimple2DImage(imageID, throwOnIDNotFound);
}

bool ImageDataListSimplifier::RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound)
{
	return _internal.RemoveMipMappedSingleSampled2DImage(imageID, throwOnIDNotFound);
}

std::uint64_t ImageDataListSimplifier::GetImageRequiredAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _internal.GetImageRequiredAligment(imageID);
}

std::uint64_t ImageDataListSimplifier::GetImageSize(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _internal.GetImageSize(imageID);
}

std::uint32_t ImageDataListSimplifier::GetImageMemoryTypeMask(IDObject<AutoCleanup2DSimpleImage> imageID) const
{
	return _internal.GetImageMemoryTypeMask(imageID);
}

std::pair<std::uint64_t, std::uint64_t> ImageDataListSimplifier::GetSizeAndAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const
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

void ImageDataListSimplifier::BindImage(IDObject<AutoCleanup2DSimpleImage> imageID, AllocationFullID allocationID, size_t addOnReserve)
{
	_internal.BindImage(imageID, allocationID, addOnReserve);
}

void ImageDataListSimplifier::BindImage(IDObject<AutoCleanupMipMapped2DImage> imageID, AllocationFullID allocationID, size_t addOnReserve)
{
	_internal.BindImage(imageID, allocationID, addOnReserve);
}

IDObject<AutoCleanupImageView> ImageDataListSimplifier::AddImageView(IDObject<AutoCleanup2DSimpleImage> imageID, size_t addOnReserve)
{
	return _internal.AddImageView(imageID, addOnReserve);
}

IDObject<AutoCleanupImageView> ImageDataListSimplifier::AddImageView(IDObject<AutoCleanupMipMapped2DImage> imageID, std::uint32_t baseMipLevel, std::uint32_t levelCount,
	size_t addOnReserve)
{
	return _internal.AddImageView(imageID, baseMipLevel, levelCount, addOnReserve);
}
