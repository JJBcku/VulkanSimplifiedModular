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

	IDObject<DescriptorSetLayoutBindingData> AddDescriptorSetLayoutBindingsData(std::uint32_t bindings, DescriptorTypeFlags descriptorType, std::uint32_t descriptorAmount,
		ShaderTypeFlags shaderStageFlags, size_t addOnReserve);

private:
	UnsortedList<DescriptorSetLayoutBindingData> _descriptorSetLayoutBindings;
};