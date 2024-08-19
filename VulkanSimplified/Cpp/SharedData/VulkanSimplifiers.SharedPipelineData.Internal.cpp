module VulkanSimplifiers.SharedPipelineData.Internal;

SharedPipelineDataInternal::SharedPipelineDataInternal(SharedPipelineDataCreationInfo initInfo) : _shaderSpecializationElements(initInfo.initialSpecializationElementsCapacity)
{
}

SharedPipelineDataInternal::~SharedPipelineDataInternal()
{
}