export module VulkanSimplifiers.Common.ImageUsageFlags;

import std;

export typedef std::uint64_t ImageUsageFlags;

export enum ImageUsageFlagBits : ImageUsageFlags
{
	IMAGE_USAGE_TRANSFER_SRC = 0x1,
	IMAGE_USAGE_TRANSFER_DST = 0x2,
	IMAGE_USAGE_SAMPLED = 0x4,
	IMAGE_USAGE_STORAGE = 0x8,
	IMAGE_USAGE_COLOR_ATTACHMENT = 0x10,
	IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT = 0x20,
	IMAGE_USAGE_TRANSIENT_ATTACHMENT = 0x40,
	IMAGE_USAGE_INPUT_ATTACHMENT = 0x80,
};