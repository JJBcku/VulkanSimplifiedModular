export module VulkanSimplifiers.DevicePipelineData.Internal;

import std;

import VulkanSimplifiers.DevicePipelineData.CreationData;

export class DevicePipelineDataInternal
{
public:
	DevicePipelineDataInternal(const DevicePipelineDataCreationData& creationInfo);
	~DevicePipelineDataInternal();

private:
	long long int stump;
};