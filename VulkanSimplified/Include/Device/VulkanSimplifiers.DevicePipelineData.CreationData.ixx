export module VulkanSimplifiers.DevicePipelineData.CreationData;

import std;

export struct DevicePipelineDataCreationData
{
	size_t pipelineLayoutListInitialCapacity;
	size_t graphicsPipelineListInitialCapacity;

	DevicePipelineDataCreationData();
};