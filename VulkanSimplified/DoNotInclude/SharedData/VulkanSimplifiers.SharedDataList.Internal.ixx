export module VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedDataList.CreationData;

import VulkanSimplifiers.SharedPipelineData.Internal;
import VulkanSimplifiers.SharedDescriptorData.Internal;
import VulkanSimplifiers.SharedRenderPassData.Internal;

export class SharedDataListInternal
{
public:
	SharedDataListInternal(const SharedDataListCreationData& creationData);
	~SharedDataListInternal();

	SharedDescriptorDataInternal& GetSharedDescriptorDataSimplifier();
	SharedPipelineDataInternal& GetSharedPipelineDataSimplifier();
	SharedRenderPassDataInternal& GetSharedRenderPassDataSimplifier();

	const SharedDescriptorDataInternal& GetSharedDescriptorDataSimplifier() const;
	const SharedPipelineDataInternal& GetSharedPipelineDataSimplifier() const;
	const SharedRenderPassDataInternal& GetSharedRenderPassDataSimplifier() const;

private:
	SharedDescriptorDataInternal _descriptorData;
	SharedPipelineDataInternal _pipelineData;
	SharedRenderPassDataInternal _renderPassData;
};
