module VulkanSimplifiers.SharedDataList.Internal;

SharedDataListInternal::SharedDataListInternal(SharedDataListCreationData creationData) : _pipelineData(creationData.sharedPipelineData)
{
}

SharedDataListInternal::~SharedDataListInternal()
{
}

SharedPipelineDataInternal& SharedDataListInternal::GetSharedPipelineDataSimplifier()
{
	return _pipelineData;
}

const SharedPipelineDataInternal& SharedDataListInternal::GetSharedPipelineDataSimplifier() const
{
	return _pipelineData;
}