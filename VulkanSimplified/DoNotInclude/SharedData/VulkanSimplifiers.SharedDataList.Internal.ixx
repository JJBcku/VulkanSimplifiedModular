export module VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedDataList.CreationData;

import VulkanSimplifiers.SharedPipelineData.Internal;

export class SharedDataListInternal
{
public:
	SharedDataListInternal(SharedDataListCreationData creationData);
	~SharedDataListInternal();

	SharedPipelineDataInternal& GetSharedPipelineDataSimplifier();

	const SharedPipelineDataInternal& GetSharedPipelineDataSimplifier() const;

private:
	SharedPipelineDataInternal _pipelineData;
};
