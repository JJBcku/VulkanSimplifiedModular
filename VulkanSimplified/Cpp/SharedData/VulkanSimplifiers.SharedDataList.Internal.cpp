module VulkanSimplifiers.SharedDataList.Internal;

SharedDataListInternal::SharedDataListInternal(const SharedDataListCreationData& creationData) : _descriptorData(creationData.sharedDescriptorData),
_pipelineData(creationData.sharedPipelineData)
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

const SharedDescriptorDataInternal& SharedDataListInternal::GetSharedDescriptorDataSimplifier() const
{
	return _descriptorData;
}

const SharedPipelineDataInternal& SharedDataListInternal::GetSharedPipelineDataSimplifier() const
{
	return _pipelineData;
}