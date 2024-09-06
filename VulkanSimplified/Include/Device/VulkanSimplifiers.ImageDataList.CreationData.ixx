export module VulkanSimplifiers.ImageDataList.CreationData;

import std;

export struct ImageDataCreationData
{
	size_t singleSampled2DImageListInitialCapacity;
	size_t singleSampledMipMapped2DListInitialCapacity;

	ImageDataCreationData();
};