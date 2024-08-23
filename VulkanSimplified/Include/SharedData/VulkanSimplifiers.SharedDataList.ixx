export module VulkanSimplifiers.SharedDataList;

import VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedPipelineData;
import VulkanSimplifiers.SharedDescriptorData;

export class SharedDataListSimplifier
{
public:
	SharedDataListSimplifier(SharedDataListInternal& ref);
	~SharedDataListSimplifier();

	SharedPipelineDataSimplifier GetSharedPipelineDataSimplifier();
	SharedDescriptorDataSimplifier GetSharedDescriptorDataSimplifier();

	const SharedPipelineDataSimplifier GetSharedPipelineDataSimplifier() const;
	const SharedDescriptorDataSimplifier GetSharedDescriptorDataSimplifier() const;

	SharedDataListSimplifier& operator=(const SharedDataListSimplifier&) noexcept = delete;

private:
	SharedDataListInternal& _internal;
};