export module VulkanSimplifiers.SharedDataList;

import VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedPipelineData;

export class SharedDataListSimplifier
{
public:
	SharedDataListSimplifier(SharedDataListInternal& ref);
	~SharedDataListSimplifier();

	SharedPipelineDataSimplifier GetSharedPipelineDataSimplifier();

	const SharedPipelineDataSimplifier GetSharedPipelineDataSimplifier() const;

	SharedDataListSimplifier& operator=(const SharedDataListSimplifier&) noexcept = delete;

private:
	SharedDataListInternal& _internal;
};