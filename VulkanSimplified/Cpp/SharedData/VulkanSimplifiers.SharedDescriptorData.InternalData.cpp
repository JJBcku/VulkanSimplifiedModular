module VulkanSimplifiers.SharedDescriptorData.InternalData;

DescriptorSetLayoutBindingData::DescriptorSetLayoutBindingData()
{
	descriptorType = static_cast<VkDescriptorType>(std::numeric_limits<std::uint32_t>::max());
	descriptorCount = std::numeric_limits<std::uint32_t>::max();
	shaderStages = std::numeric_limits<std::uint32_t>::max();
	padding = 0;
}