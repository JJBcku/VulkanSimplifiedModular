export module VulkanSimplifiers.ShaderList.Data;

import std;
import ListTemplates.IDObject;

export import VulkanSimplifiers.Common.ShaderTypeFlags;

export class AutoCleanUpFragmentShader;
export class AutoCleanUpVertexShader;

export union ArbitraryShaderID
{
public:
	ShaderTypeFlagBit type;

	struct
	{
		ShaderTypeFlagBit type;
		IDObject<AutoCleanUpFragmentShader> fragmentShaderID;
	} fragmentShader;

	struct
	{
		ShaderTypeFlagBit type;
		IDObject<AutoCleanUpVertexShader> vertexShaderID;
	} vertexShader;

	ArbitraryShaderID();
	ArbitraryShaderID(IDObject<AutoCleanUpFragmentShader> fragmentShaderID);
	ArbitraryShaderID(IDObject<AutoCleanUpVertexShader> vertexShaderID);
};