module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Common.DataFormatFlags.Internal;

import std;
export import VulkanSimplifiers.Common.DataFormatFlags;

export VkFormat TranslateDataFormatToVkFormat(DataFormatSetIndependentID formatID);