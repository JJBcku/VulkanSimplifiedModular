export module VulkanSimplifiers.DeviceDescriptorData.Internal;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.DeviceDescriptorData.CreationData;

export class DeviceDescriptorDataInternal
{
public:
	DeviceDescriptorDataInternal(const DeviceDesriptorDataCreationData& creationData);
	~DeviceDescriptorDataInternal();

private:
	std::uint64_t stump;
};