module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Common.PipelineStageFlags.Internal;

export import VulkanSimplifiers.Common.PipelineStageFlags;

export VkPipelineStageFlags TranslateStageFlags(PipelineStageFlags stageFlags);