module VulkanSimplifiers.SharedDataList.Internal;

SharedDataListInternal::SharedDataListInternal(const SharedDataListCreationData& creationData) : _descriptorData(creationData.sharedDescriptorData),
_pipelineData(creationData.sharedPipelineData), _renderPassData(creationData.sharedRenderPassData)
{
}

SharedDataListInternal::~SharedDataListInternal()
{
}

SharedDescriptorDataInternal& SharedDataListInternal::GetSharedDescriptorDataSimplifier()
{
	return _descriptorData;
}

SharedPipelineDataInternal& SharedDataListInternal::GetSharedPipelineDataSimplifier()
{
	return _pipelineData;
}

SharedRenderPassDataInternal& SharedDataListInternal::GetSharedRenderPassDataSimplifier()
{
	return _renderPassData;
}

const SharedDescriptorDataInternal& SharedDataListInternal::GetSharedDescriptorDataSimplifier() const
{
	return _descriptorData;
}

const SharedPipelineDataInternal& SharedDataListInternal::GetSharedPipelineDataSimplifier() const
{
	return _pipelineData;
}

const SharedRenderPassDataInternal& SharedDataListInternal::GetSharedRenderPassDataSimplifier() const
{
	return _renderPassData;
}