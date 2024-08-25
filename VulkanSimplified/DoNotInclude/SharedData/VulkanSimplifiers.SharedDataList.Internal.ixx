export module VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedDataList.CreationData;

import VulkanSimplifiers.SharedPipelineData.Internal;
import VulkanSimplifiers.SharedDescriptorData.Internal;

export class SharedDataListInternal
{
public:
	SharedDataListInternal(const SharedDataListCreationData& creationData);
	~SharedDataListInternal();

	SharedDescriptorDataInternal& GetSharedDescriptorDataSimplifier();
	SharedPipelineDataInternal& GetSharedPipelineDataSimplifier();

	const SharedDescriptorDataInternal& GetSharedDescriptorDataSimplifier() const;
	const SharedPipelineDataInternal& GetSharedPipelineDataSimplifier() const;

private:
	SharedDescriptorDataInternal _descriptorData;
	SharedPipelineDataInternal _pipelineData;
};
