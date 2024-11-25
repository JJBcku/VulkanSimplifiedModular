export module VulkanSimplifiers.ShaderList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.ShaderList.Internal;
import VulkanSimplifiers.ShaderList.Data;

export class ShaderListSimplifier
{
public:
	ShaderListSimplifier(ShaderListInternal& ref);
	~ShaderListSimplifier();

	ShaderListSimplifier& operator=(const ShaderListSimplifier&) noexcept = delete;

	IDObject<AutoCleanUpFragmentShader> AddFragmentShader(const std::vector<char>& shaderCode, size_t addOnResize = 0);
	IDObject<AutoCleanUpVertexShader> AddVertexShader(const std::vector<char>& shaderCode, size_t addOnResize = 0);

private:
	ShaderListInternal& _internal;
};