export module VulkanSimplifiers.SharedDataList;

import VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedPipelineData;
import VulkanSimplifiers.SharedDescriptorData;
import VulkanSimplifiers.SharedRenderPassData;

export class SharedDataListSimplifier
{
public:
	SharedDataListSimplifier(SharedDataListInternal& ref);
	~SharedDataListSimplifier();

	SharedPipelineDataSimplifier GetSharedPipelineDataSimplifier();
	SharedDescriptorDataSimplifier GetSharedDescriptorDataSimplifier();
	SharedRenderPassDataSimplifier GetSharedRenderPassDataSimplifier();

	const SharedPipelineDataSimplifier GetSharedPipelineDataSimplifier() const;
	const SharedDescriptorDataSimplifier GetSharedDescriptorDataSimplifier() const;
	const SharedRenderPassDataSimplifier GetSharedRenderPassDataSimplifier() const;

	SharedDataListSimplifier& operator=(const SharedDataListSimplifier&) noexcept = delete;

private:
	SharedDataListInternal& _internal;
};