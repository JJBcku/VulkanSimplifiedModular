export module VulkanSimplifiers.DeviceRenderPassData.Internal;

import std;

import VulkanSimplifiers.DeviceRenderPassData.CreationData;

export class DeviceRenderPassDataInternal
{
public:
	DeviceRenderPassDataInternal(const DeviceRenderPassCreationData& creationData);
	~DeviceRenderPassDataInternal();

private:
	std::uint64_t stump;
};