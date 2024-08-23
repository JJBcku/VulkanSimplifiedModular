export module VulkanSimplifiers.SharedDescriptorData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SharedDescriptorData.Internal;
import VulkanSimplifiers.SharedDescriptorData.Data;

import VulkanSimplifiers.Common.DescriptorTypeFlags;
import VulkanSimplifiers.Common.ShaderTypeFlags;

export class SharedDescriptorDataSimplifier
{
public:
	SharedDescriptorDataSimplifier(SharedDescriptorDataInternal& ref);
	~SharedDescriptorDataSimplifier();

	SharedDescriptorDataSimplifier& operator=(const SharedDescriptorDataSimplifier&) noexcept = delete;

	IDObject<DescriptorSetLayoutBindingData> AddDescriptorSetLayoutBindingsData(DescriptorTypeFlags descriptorType, std::uint32_t descriptorAmount,
		ShaderTypeFlags shaderStageFlags, size_t addOnReserve = 0);

private:
	SharedDescriptorDataInternal& _internal;
};