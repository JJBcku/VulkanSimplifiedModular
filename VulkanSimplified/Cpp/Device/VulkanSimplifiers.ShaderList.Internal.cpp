module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.ShaderList.Internal;

ShaderListInternal::ShaderListInternal(const ShaderListCreationData& initData, VkDevice device) : _device(device), _fragmentShaders(initData.initialFragmentListCapacity),
_vertexShaders(initData.initialVertexListCapacity)
{
}

ShaderListInternal::~ShaderListInternal()
{
}