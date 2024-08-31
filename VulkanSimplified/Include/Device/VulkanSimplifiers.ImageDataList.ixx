export module VulkanSimplifiers.ImageDataList;

import VulkanSimplifiers.ImageDataList.Internal;

export class ImageDataListSimplifier
{
public:
	ImageDataListSimplifier(ImageDataListInternal& ref);
	~ImageDataListSimplifier();

	ImageDataListSimplifier& operator=(const ImageDataListSimplifier&) noexcept = delete;

private:
	ImageDataListInternal& _internal;
};