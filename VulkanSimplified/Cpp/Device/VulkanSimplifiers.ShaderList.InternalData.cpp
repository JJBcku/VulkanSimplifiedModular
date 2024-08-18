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

AutoCleanUpShader::AutoCleanUpShader(AutoCleanUpShader&& rhs) noexcept : _device(rhs._device), _shader(rhs._shader)
{
	rhs._device = VK_NULL_HANDLE;
	rhs._shader = VK_NULL_HANDLE;
}

AutoCleanUpShader& AutoCleanUpShader::operator=(AutoCleanUpShader&& rhs) noexcept
{
	_device = rhs._device;
	_shader = rhs._shader;

	rhs._device = VK_NULL_HANDLE;
	rhs._shader = VK_NULL_HANDLE;

	return *this;
}

AutoCleanUpFragmentShader::AutoCleanUpFragmentShader(VkDevice device, VkShaderModule shader) : AutoCleanUpShader(device, shader)
{
}

AutoCleanUpFragmentShader::~AutoCleanUpFragmentShader()
{
}

AutoCleanUpFragmentShader::AutoCleanUpFragmentShader(AutoCleanUpFragmentShader&& rhs) noexcept : AutoCleanUpShader(std::move(rhs))
{
}

AutoCleanUpFragmentShader& AutoCleanUpFragmentShader::operator=(AutoCleanUpFragmentShader&& rhs) noexcept
{
	*static_cast<AutoCleanUpShader*>(this) = std::move(*static_cast<AutoCleanUpShader*>(&rhs));

	return *this;
}

AutoCleanUpVertexShader::AutoCleanUpVertexShader(VkDevice device, VkShaderModule shader) : AutoCleanUpShader(device, shader)
{
}

AutoCleanUpVertexShader::~AutoCleanUpVertexShader()
{
}

AutoCleanUpVertexShader::AutoCleanUpVertexShader(AutoCleanUpVertexShader&& rhs) noexcept : AutoCleanUpShader(std::move(rhs))
{
}

AutoCleanUpVertexShader& AutoCleanUpVertexShader::operator=(AutoCleanUpVertexShader&& rhs) noexcept
{
	*static_cast<AutoCleanUpShader*>(this) = std::move(*static_cast<AutoCleanUpShader*>(&rhs));

	return *this;
}
