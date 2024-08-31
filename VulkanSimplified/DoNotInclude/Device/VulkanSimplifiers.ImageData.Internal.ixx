export module VulkanSimplifiers.ImageDataList.Internal;

import std;

import VulkanSimplifiers.ImageDataList.CreationData;

export class ImageDataListInternal
{
public:
	ImageDataListInternal(const ImageDataCreationData& creationData);
	~ImageDataListInternal();

private:
	std::uint64_t stump;
};