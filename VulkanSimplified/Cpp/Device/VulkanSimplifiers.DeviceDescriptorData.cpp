module VulkanSimplifiers.DeviceDescriptorData;

DeviceDescriptorDataSimpifier::DeviceDescriptorDataSimpifier(DeviceDescriptorDataInternal& ref) : _internal(ref)
{
}

DeviceDescriptorDataSimpifier::~DeviceDescriptorDataSimpifier()
{
}

IDObject<AutoCleanupDescriptorSetLayout> DeviceDescriptorDataSimpifier::AddDescriptorSetLayout(std::uint32_t firstBinding,
	const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserve)
{
	return _internal.AddDescriptorSetLayout(firstBinding, descriptorSetLayoutBindings, addOnReserve);
}
