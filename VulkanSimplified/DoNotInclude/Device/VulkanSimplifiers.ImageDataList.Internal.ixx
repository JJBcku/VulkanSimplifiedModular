module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.ImageDataList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.ImageDataList.CreationData;
import VulkanSimplifiers.ImageDataList.InternalData;

import VulkanSimplifiers.Common.DataFormatFlags.Internal;
import VulkanSimplifiers.Common.ImageUsageFlags.Internal;

import VulkanSimplifiers.LogicalDeviceCore.Internal;

export class ImageDataListInternal
{
public:
	ImageDataListInternal(const ImageDataCreationData& creationData, const LogicalDeviceCoreInternal& deviceCore, VkDevice device);
	~ImageDataListInternal();

	ImageDataListInternal& operator=(const ImageDataListInternal&) noexcept = delete;

	IDObject<AutoCleanup2DImage> AddSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserve);
	IDObject<AutoCleanupMipMapped2DImage> AddMipMappedSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool calculateMipmapsFromBiggestSize, size_t initialImageViewListCapacity, size_t addOnReserve);

	bool RemoveSingleSampled2DImage(IDObject<AutoCleanup2DImage> imageID, bool throwOnIDNotFound);
	bool RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound);

private:
	const LogicalDeviceCoreInternal& _deviceCore;
	VkDevice _device;

	UnsortedList<AutoCleanup2DImage> _singleSampled2DImage;
	UnsortedList<AutoCleanupMipMapped2DImage> _singleSampledMipMapped2DImage;

	std::uint32_t CalculateMipmapLevelsFromBiggest3D(std::uint32_t width, std::uint32_t height, std::uint32_t depth) const;
	std::uint32_t CalculateMipmapLevelsFromBiggest2D(std::uint32_t width, std::uint32_t height) const;

	std::uint32_t CalculateMipmapLevelsFromSmallest3D(std::uint32_t width, std::uint32_t height, std::uint32_t depth) const;
	std::uint32_t CalculateMipmapLevelsFromSmallest2D(std::uint32_t width, std::uint32_t height) const;
};