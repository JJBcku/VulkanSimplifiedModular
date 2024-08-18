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

IDObject<AutoCleanUpFragmentShader> ShaderListInternal::AddFragmentShader(const std::vector<char>& shaderCode, size_t addOnResize)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = shaderCode.size();
	createInfo.pCode = reinterpret_cast<const std::uint32_t*>(shaderCode.data());

	VkShaderModule add = VK_NULL_HANDLE;

	if (vkCreateShaderModule(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("ShaderListInternal::AddFragmentShader Error: Program failed to create shader module!");

	return _fragmentShaders.AddObject(AutoCleanUpFragmentShader(_device, add), addOnResize);
}

IDObject<AutoCleanUpVertexShader> ShaderListInternal::AddVertexShader(const std::vector<char>& shaderCode, size_t addOnResize)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = shaderCode.size();
	createInfo.pCode = reinterpret_cast<const std::uint32_t*>(shaderCode.data());

	VkShaderModule add = VK_NULL_HANDLE;

	if (vkCreateShaderModule(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("ShaderListInternal::AddVertexShader Error: Program failed to create shader module!");

	return _vertexShaders.AddObject(AutoCleanUpVertexShader(_device, add), addOnResize);
}
