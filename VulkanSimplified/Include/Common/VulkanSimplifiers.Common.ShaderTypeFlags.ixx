export module VulkanSimplifiers.Common.ShaderTypeFlags;

import std;

export typedef std::uint64_t ShaderTypeFlags;

export enum ShaderTypeFlagBit : ShaderTypeFlags
{
	SHADER_TYPE_FRAGMENT = 0x1,
	SHADER_TYPE_VERTEX = 0x2,
};