export module VulkanSimplifiers.SharedPipelineData;

import VulkanSimplifiers.SharedPipelineData.Internal;

export class SharedPipelineDataSimplifier
{
public:
	SharedPipelineDataSimplifier(SharedPipelineDataInternal& ref);
	~SharedPipelineDataSimplifier();

	SharedPipelineDataSimplifier& operator=(const SharedPipelineDataSimplifier&) noexcept = delete;

private:
	SharedPipelineDataInternal& _internal;
};