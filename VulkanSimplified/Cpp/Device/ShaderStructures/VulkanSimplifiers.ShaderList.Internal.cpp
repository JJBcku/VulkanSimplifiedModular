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
	if (shaderCode.size() == 0)
		throw std::runtime_error("ShaderListInternal::AddFragmentShader Error: Program tried to create an empty shader!");

	if (shaderCode.size() % 4 != 0)
		throw std::runtime_error("ShaderListInternal::AddFragmentShader Error: Program tried to use code with size that is not a multiplication of four!");

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
	if (shaderCode.size() == 0)
		throw std::runtime_error("ShaderListInternal::AddVertexShader Error: Program tried to create an empty shader!");

	if (shaderCode.size() % 4 != 0)
		throw std::runtime_error("ShaderListInternal::AddVertexShader Error: Program tried to use code with size that is not a multiplication of four!");

	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = shaderCode.size();
	createInfo.pCode = reinterpret_cast<const std::uint32_t*>(shaderCode.data());

	VkShaderModule add = VK_NULL_HANDLE;

	if (vkCreateShaderModule(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("ShaderListInternal::AddVertexShader Error: Program failed to create shader module!");

	return _vertexShaders.AddObject(AutoCleanUpVertexShader(_device, add), addOnResize);
}

VkShaderModule ShaderListInternal::GetShaderModule(ArbitraryShaderID shaderID) const
{
	VkShaderModule ret = VK_NULL_HANDLE;

	switch (shaderID.type)
	{
	case SHADER_TYPE_FRAGMENT:
		ret = GetFragmentShader(shaderID.fragmentShader.fragmentShaderID);
		break;
	case SHADER_TYPE_VERTEX:
		ret = GetVertexShader(shaderID.vertexShader.vertexShaderID);
		break;
	default:
		throw std::runtime_error("ShaderListInternal::GetShaderModule Error: Program was given an erroneous shader id type!");
	}

	return ret;
}

VkShaderModule ShaderListInternal::GetFragmentShader(IDObject<AutoCleanUpFragmentShader> shaderID) const
{
	return _fragmentShaders.GetConstObject(shaderID).GetShaderModule();
}

VkShaderModule ShaderListInternal::GetVertexShader(IDObject<AutoCleanUpVertexShader> shaderID) const
{
	return _vertexShaders.GetConstObject(shaderID).GetShaderModule();
}
