module VulkanSimplifiers.SharedDataList.Internal;

SharedDataListInternal::SharedDataListInternal(const SharedDataListCreationData& creationData) : _pipelineData(creationData.sharedPipelineData),
_descriptorData(creationData.sharedDescriptorData)
{
}

SharedDataListInternal::~SharedDataListInternal()
{
}

SharedPipelineDataInternal& SharedDataListInternal::GetSharedPipelineDataSimplifier()
{
	return _pipelineData;
}

SharedDescriptorDataInternal& SharedDataListInternal::GetSharedDescriptorDataSimplifier()
{
	return _descriptorData;
}

const SharedPipelineDataInternal& SharedDataListInternal::GetSharedPipelineDataSimplifier() const
{
	return _pipelineData;
}

const SharedDescriptorDataInternal& SharedDataListInternal::GetSharedDescriptorDataSimplifier() const
{
	return _descriptorData;
}