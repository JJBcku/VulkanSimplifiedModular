module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Common.ImageLayouts.Internal;

export import VulkanSimplifiers.Common.ImageLayouts;

export VkImageLayout TranslateImageLayout(ImageLayoutFlags imageLayout);