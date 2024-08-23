export module VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedDataList.CreationData;

import VulkanSimplifiers.SharedPipelineData.Internal;
import VulkanSimplifiers.SharedDescriptorData.Internal;

export class SharedDataListInternal
{
public:
	SharedDataListInternal(const SharedDataListCreationData& creationData);
	~SharedDataListInternal();

	SharedPipelineDataInternal& GetSharedPipelineDataSimplifier();
	SharedDescriptorDataInternal& GetSharedDescriptorDataSimplifier();

	const SharedPipelineDataInternal& GetSharedPipelineDataSimplifier() const;
	const SharedDescriptorDataInternal& GetSharedDescriptorDataSimplifier() const;

private:
	SharedPipelineDataInternal _pipelineData;
	SharedDescriptorDataInternal _descriptorData;
};
