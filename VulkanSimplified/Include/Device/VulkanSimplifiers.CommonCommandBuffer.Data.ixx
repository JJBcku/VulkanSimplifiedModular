export module VulkanSimplifiers.CommonCommandBuffer.Data;

import std;

export enum class CommandBufferUsage : std::uint64_t
{
	ONE_USE = 0x1,
	MULTIPLE_USE_NO_SIMULTANEOUS_USAGE = 0x2,
	MULTIPLE_USE_SIMULTANEOUS_USAGE = 0x4,
};