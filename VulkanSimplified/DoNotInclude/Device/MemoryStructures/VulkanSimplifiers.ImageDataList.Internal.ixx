module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.ImageDataList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.ImageDataList.CreationData;
import VulkanSimplifiers.ImageDataList.InternalData;
import VulkanSimplifiers.ImageDataList.Data;

import VulkanSimplifiers.Common.DataFormatFlags.Internal;
import VulkanSimplifiers.Common.ImageUsageFlags.Internal;

import VulkanSimplifiers.LogicalDeviceCore.Internal;
import VulkanSimplifiers.MemoryObjectsList.Internal;

import VulkanSimplifiers.DeviceRenderPassData.Internal;

export class ImageDataListInternal
{
public:
	ImageDataListInternal(const ImageDataCreationData& creationData, const LogicalDeviceCoreInternal& deviceCore, const DeviceRenderPassDataInternal& renderPassData,
		MemoryObjectsListInternal& memoryList, VkDevice device);
	~ImageDataListInternal();

	ImageDataListInternal& operator=(const ImageDataListInternal&) noexcept = delete;

	IDObject<AutoCleanup2DSimpleImage> AddSimple2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserve);
	IDObject<AutoCleanupMipMapped2DImage> AddMipMappedSingleSampled2DImage(std::uint32_t width, std::uint32_t height, DataFormatSetIndependentID format, ImageUsageFlags usageFlags,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool calculateMipmapsFromBiggestSize, size_t initialImageViewListCapacity, size_t addOnReserve);

	bool RemoveSimple2DImage(IDObject<AutoCleanup2DSimpleImage> imageID, bool throwOnIDNotFound);
	bool RemoveMipMappedSingleSampled2DImage(IDObject<AutoCleanupMipMapped2DImage> imageID, bool throwOnIDNotFound);

	std::uint64_t GetImageRequiredAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const;
	std::uint64_t GetImageSize(IDObject<AutoCleanup2DSimpleImage> imageID) const;
	std::uint32_t GetImageMemoryTypeMask(IDObject<AutoCleanup2DSimpleImage> imageID) const;

	std::pair<std::uint64_t, std::uint64_t> GetSizeAndAligment(IDObject<AutoCleanup2DSimpleImage> imageID) const;

	std::uint64_t GetImageRequiredAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const;
	std::uint64_t GetImageSize(IDObject<AutoCleanupMipMapped2DImage> imageID) const;
	std::uint32_t GetImageMemoryTypeMask(IDObject<AutoCleanupMipMapped2DImage> imageID) const;

	std::pair<std::uint64_t, std::uint64_t> GetSizeAndAligment(IDObject<AutoCleanupMipMapped2DImage> imageID) const;

	void BindImage(IDObject<AutoCleanup2DSimpleImage> imageID, AllocationFullID allocationID, size_t addOnReserve);
	void BindImage(IDObject<AutoCleanupMipMapped2DImage> imageID, AllocationFullID allocationID, size_t addOnReserve);

	IDObject<AutoCleanupImageView> AddImageView(IDObject<AutoCleanup2DSimpleImage> imageID, size_t addOnReserve);
	IDObject<AutoCleanupImageView> AddImageView(IDObject<AutoCleanupMipMapped2DImage> imageID, std::uint32_t baseMipLevel, std::uint32_t levelCount, size_t addOnReserve);

	VkImageView GetImageView(IDObject<AutoCleanup2DSimpleImage> imageID, IDObject<AutoCleanupImageView> viewID) const;
	VkImageView GetImageView(IDObject<AutoCleanupMipMapped2DImage> imageID, IDObject<AutoCleanupImageView> viewID) const;

	IDObject<AutoCleanupFramebuffer> AddFramebuffer(IDObject<AutoCleanupRenderPass> renderPass,
		const std::vector<std::pair<ImageIDUnion, IDObject<AutoCleanupImageView>>>& attachmentsList, std::uint32_t width, std::uint32_t height, std::uint32_t layers,
		size_t addOnReserve);

	bool RemoveFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound);

	VkFramebuffer GetFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID) const;

private:
	const LogicalDeviceCoreInternal& _deviceCore;
	const DeviceRenderPassDataInternal& _renderPassData;
	MemoryObjectsListInternal& _memoryList;
	VkDevice _device;

	UnsortedList<AutoCleanup2DSimpleImage> _singleSampled2DImage;
	UnsortedList<AutoCleanupMipMapped2DImage> _singleSampledMipMapped2DImage;

	UnsortedList<AutoCleanupFramebuffer> _framebuffersList;

	std::uint32_t CalculateMipmapLevelsFromBiggest3D(std::uint32_t width, std::uint32_t height, std::uint32_t depth) const;
	std::uint32_t CalculateMipmapLevelsFromBiggest2D(std::uint32_t width, std::uint32_t height) const;

	std::uint32_t CalculateMipmapLevelsFromSmallest3D(std::uint32_t width, std::uint32_t height, std::uint32_t depth) const;
	std::uint32_t CalculateMipmapLevelsFromSmallest2D(std::uint32_t width, std::uint32_t height) const;
};