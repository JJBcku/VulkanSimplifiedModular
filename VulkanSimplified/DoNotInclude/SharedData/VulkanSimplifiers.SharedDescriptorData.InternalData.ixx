module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedDescriptorData.InternalData;

import std;

export struct DescriptorSetLayoutBindingData
{
	std::uint32_t binding;
	VkDescriptorType descriptorType;
	std::uint32_t descriptorCount;
	VkShaderStageFlags shaderStages;

	DescriptorSetLayoutBindingData();

	bool operator==(const DescriptorSetLayoutBindingData&) const noexcept = default;
	std::strong_ordering operator<=>(const DescriptorSetLayoutBindingData&) const noexcept = default;
};