module VulkanSimplifiers.ShaderList.Data;

ArbitraryShaderID::ArbitraryShaderID()
{
	type = static_cast<ShaderTypeFlagBit>(0);
}

ArbitraryShaderID::ArbitraryShaderID(IDObject<AutoCleanUpFragmentShader> fragmentShaderID)
{
	type = SHADER_TYPE_FRAGMENT;
	fragmentShader.fragmentShaderID = fragmentShaderID;
}

ArbitraryShaderID::ArbitraryShaderID(IDObject<AutoCleanUpVertexShader> vertexShaderID)
{
	type = SHADER_TYPE_VERTEX;
	vertexShader.vertexShaderID = vertexShaderID;
}