export module VulkanSimplifiers.ShaderList.CreationData;

export struct ShaderListCreationData
{
	size_t initialFragmentListCapacity;
	size_t initialVertexListCapacity;

	ShaderListCreationData();
};