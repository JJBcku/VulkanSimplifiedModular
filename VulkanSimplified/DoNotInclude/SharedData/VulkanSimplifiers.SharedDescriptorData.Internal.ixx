module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedDescriptorData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SharedDescriptorData.CreationData;
import VulkanSimplifiers.SharedDescriptorData.InternalData;

import VulkanSimplifiers.Common.DescriptorTypeFlags;
import VulkanSimplifiers.Common.ShaderTypeFlags;

export class SharedDescriptorDataInternal
{
public:
	SharedDescriptorDataInternal(const SharedDescriptorDataCreationInfo& creationInfo);
	~SharedDescriptorDataInternal();

	IDObject<DescriptorSetLayoutBindingData> AddDescriptorSetLayoutBindingsData(DescriptorTypeFlags descriptorType, std::uint32_t descriptorAmount,
		ShaderTypeFlags shaderStageFlags, size_t addOnReserve);

	std::vector<VkDescriptorSetLayoutBinding> GetDescriptorSetLayoutBindings(std::uint32_t firstBinding, const std::vector<IDObject<DescriptorSetLayoutBindingData>>& bindingIDs) const;

private:
	UnsortedList<DescriptorSetLayoutBindingData> _descriptorSetLayoutBindings;
};