module VulkanSimplifiers.ShaderList;

ShaderListSimplifier::ShaderListSimplifier(ShaderListInternal& ref) : _internal(ref)
{
}

ShaderListSimplifier::~ShaderListSimplifier()
{
}

IDObject<AutoCleanUpFragmentShader> ShaderListSimplifier::AddFragmentShader(const std::vector<char>& shaderCode, size_t addOnResize)
{
	return _internal.AddFragmentShader(shaderCode, addOnResize);
}

IDObject<AutoCleanUpVertexShader> ShaderListSimplifier::AddVertexShader(const std::vector<char>& shaderCode, size_t addOnResize)
{
	return _internal.AddVertexShader(shaderCode, addOnResize);
}
