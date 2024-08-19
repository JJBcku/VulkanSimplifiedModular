export module VulkanSimplifiers.ShaderList.Data;

import std;
import ListTemplates.IDObject;

export class AutoCleanUpFragmentShader;
export class AutoCleanUpVertexShader;

export enum class ShaderIDType : std::uint64_t
{
	UNKNOWN = 0,
	FRAGMENT = 1,
	VERTEX = 2,
};

export union ArbitraryShaderID
{
public:
	ShaderIDType type;

	struct
	{
		ShaderIDType type;
		IDObject<AutoCleanUpFragmentShader> fragmentShaderID;
	} fragmentShader;

	struct
	{
		ShaderIDType type;
		IDObject<AutoCleanUpVertexShader> vertexShaderID;
	} vertexShader;

	ArbitraryShaderID();
};