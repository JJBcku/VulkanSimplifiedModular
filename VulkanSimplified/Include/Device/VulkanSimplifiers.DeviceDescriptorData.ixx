export module VulkanSimplifiers.DeviceDescriptorData;

import std;
import VulkanSimplifiers.DeviceDescriptorData.Internal;

export class DeviceDescriptorDataSimpifier
{
public:
	DeviceDescriptorDataSimpifier(DeviceDescriptorDataInternal& ref);
	~DeviceDescriptorDataSimpifier();

	DeviceDescriptorDataSimpifier& operator=(const DeviceDescriptorDataSimpifier&) noexcept = delete;

private:
	DeviceDescriptorDataInternal& _internal;
};