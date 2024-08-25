export module VulkanSimplifiers.DevicePipelineData;

import VulkanSimplifiers.DevicePipelineData.Internal;

export class DevicePipelineDataSimplifier
{
public:
	DevicePipelineDataSimplifier(DevicePipelineDataInternal& ref);
	~DevicePipelineDataSimplifier();

	DevicePipelineDataSimplifier& operator=(const DevicePipelineDataSimplifier&) noexcept = delete;

private:
	DevicePipelineDataInternal& _internal;
};