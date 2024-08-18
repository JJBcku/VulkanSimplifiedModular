module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.ShaderList.InternalData;

AutoCleanUpShader::AutoCleanUpShader(VkDevice device, VkShaderModule shader) : _device(device), _shader(shader)
{
}

AutoCleanUpShader::~AutoCleanUpShader()
{
	if (_shader != VK_NULL_HANDLE)
	{
		vkDestroyShaderModule(_device, _shader, nullptr);
	}
}

AutoCleanUpFragmentShader::AutoCleanUpFragmentShader(VkDevice device, VkShaderModule shader) : AutoCleanUpShader(device, shader)
{
}

AutoCleanUpFragmentShader::~AutoCleanUpFragmentShader()
{
}

AutoCleanUpVertexShader::AutoCleanUpVertexShader(VkDevice device, VkShaderModule shader) : AutoCleanUpShader(device, shader)
{
}

AutoCleanUpVertexShader::~AutoCleanUpVertexShader()
{
}