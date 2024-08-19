module VulkanSimplifiers.SharedDataList;

SharedDataListSimplifier::SharedDataListSimplifier(SharedDataListInternal& ref) : _internal(ref)
{
}

SharedDataListSimplifier::~SharedDataListSimplifier()
{
}

SharedPipelineDataSimplifier SharedDataListSimplifier::GetSharedPipelineDataSimplifier()
{
	return _internal.GetSharedPipelineDataSimplifier();
}

const SharedPipelineDataSimplifier SharedDataListSimplifier::GetSharedPipelineDataSimplifier() const
{
	return _internal.GetSharedPipelineDataSimplifier();
}