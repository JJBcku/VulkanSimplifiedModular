export module VulkanSimplifiers.DeviceRenderPassData;

import VulkanSimplifiers.DeviceRenderPassData.Internal;

export class DeviceRenderPassDataSimplifier
{
public:
	DeviceRenderPassDataSimplifier(DeviceRenderPassDataInternal& ref);
	~DeviceRenderPassDataSimplifier();

	DeviceRenderPassDataSimplifier& operator=(const DeviceRenderPassDataSimplifier&) noexcept = delete;

private:
	DeviceRenderPassDataInternal& _internal;
};