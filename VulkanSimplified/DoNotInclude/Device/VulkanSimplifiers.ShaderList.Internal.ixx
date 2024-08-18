module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.ShaderList.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.ShaderList.InternalData;
import VulkanSimplifiers.ShaderList.CreationData;

export class ShaderListInternal
{
public:
	ShaderListInternal(const ShaderListCreationData& initData, VkDevice device);
	~ShaderListInternal();

	IDObject<AutoCleanUpFragmentShader> AddFragmentShader(const std::vector<char>& shaderCode, size_t addOnResize);
	IDObject<AutoCleanUpVertexShader> AddVertexShader(const std::vector<char>& shaderCode, size_t addOnResize);

private:
	VkDevice _device;

	UnsortedList<AutoCleanUpFragmentShader> _fragmentShaders;
	UnsortedList<AutoCleanUpVertexShader> _vertexShaders;
};