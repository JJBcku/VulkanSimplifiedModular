export module VulkanSimplifiers.Instance;

import VulkanSimplifiers.Instance.Internal;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.DeviceList.Internal;

export class InstanceSimplifier
{
public:
	InstanceSimplifier(InstanceInternal& ref);
	~InstanceSimplifier();

	InstanceSimplifier& operator=(const InstanceSimplifier&) noexcept = delete;

	DeviceListSimplifier GetDeviceListSimplifier();

private:
	InstanceInternal& _internal;
};