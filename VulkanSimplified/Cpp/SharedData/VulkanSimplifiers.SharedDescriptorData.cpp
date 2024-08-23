module VulkanSimplifiers.SharedDescriptorData;

SharedDescriptorDataSimplifier::SharedDescriptorDataSimplifier(SharedDescriptorDataInternal& ref) : _internal(ref)
{

}

SharedDescriptorDataSimplifier::~SharedDescriptorDataSimplifier()
{
}

IDObject<DescriptorSetLayoutBindingData> SharedDescriptorDataSimplifier::AddDescriptorSetLayoutBindingsData(std::uint32_t bindings, DescriptorTypeFlags descriptorType,
	std::uint32_t descriptorAmount, ShaderTypeFlags shaderStageFlags, size_t addOnReserve)
{
	return _internal.AddDescriptorSetLayoutBindingsData(bindings, descriptorType, descriptorAmount, shaderStageFlags, addOnReserve);
}
