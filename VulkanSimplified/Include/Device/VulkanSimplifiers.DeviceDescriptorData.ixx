export module VulkanSimplifiers.DeviceDescriptorData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.DeviceDescriptorData.Internal;
import VulkanSimplifiers.DeviceDescriptorData.Data;

export class DeviceDescriptorDataSimpifier
{
public:
	DeviceDescriptorDataSimpifier(DeviceDescriptorDataInternal& ref);
	~DeviceDescriptorDataSimpifier();

	DeviceDescriptorDataSimpifier& operator=(const DeviceDescriptorDataSimpifier&) noexcept = delete;

	IDObject<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(std::uint32_t firstBinding, const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings,
		size_t addOnReserve = 0);

private:
	DeviceDescriptorDataInternal& _internal;
};