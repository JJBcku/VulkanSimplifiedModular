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

SharedDescriptorDataSimplifier SharedDataListSimplifier::GetSharedDescriptorDataSimplifier()
{
	return _internal.GetSharedDescriptorDataSimplifier();
}

SharedRenderPassDataSimplifier SharedDataListSimplifier::GetSharedRenderPassDataSimplifier()
{
	return _internal.GetSharedRenderPassDataSimplifier();
}

const SharedPipelineDataSimplifier SharedDataListSimplifier::GetSharedPipelineDataSimplifier() const
{
	return _internal.GetSharedPipelineDataSimplifier();
}

const SharedDescriptorDataSimplifier SharedDataListSimplifier::GetSharedDescriptorDataSimplifier() const
{
	return _internal.GetSharedDescriptorDataSimplifier();
}

const SharedRenderPassDataSimplifier SharedDataListSimplifier::GetSharedRenderPassDataSimplifier() const
{
	return _internal.GetSharedRenderPassDataSimplifier();
}