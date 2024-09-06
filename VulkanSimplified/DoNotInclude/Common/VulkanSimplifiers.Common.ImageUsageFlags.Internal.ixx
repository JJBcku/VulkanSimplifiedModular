module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Common.ImageUsageFlags.Internal;

import std;

export import VulkanSimplifiers.Common.ImageUsageFlags;

export VkImageUsageFlags TranslateImageUsage(ImageUsageFlags usageFlags);
