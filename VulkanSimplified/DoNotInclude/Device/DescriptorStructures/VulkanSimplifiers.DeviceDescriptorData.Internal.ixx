module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DeviceDescriptorData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.DeviceDescriptorData.CreationData;
import VulkanSimplifiers.DeviceDescriptorData.InternalData;
import VulkanSimplifiers.DeviceDescriptorData.Data;

import VulkanSimplifiers.SharedDescriptorData.Internal;

export class DeviceDescriptorDataInternal
{
public:
	DeviceDescriptorDataInternal(const DeviceDescriptorDataCreationData& creationData, const VkDevice device, const SharedDescriptorDataInternal& sharedDescriptorData);
	~DeviceDescriptorDataInternal();

	DeviceDescriptorDataInternal& operator=(const DeviceDescriptorDataInternal&) noexcept = delete;

	IDObject<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(std::uint32_t firstBinding, const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings,
		size_t addOnReserve);

	std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const;

private:
	const VkDevice _device;
	const SharedDescriptorDataInternal& _sharedDescriptorData;

	UnsortedList<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;
};