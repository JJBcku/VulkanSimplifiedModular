module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DeviceDescriptorData.Internal;

DeviceDescriptorDataInternal::DeviceDescriptorDataInternal(const DeviceDescriptorDataCreationData& creationData, const VkDevice device,
	const SharedDescriptorDataInternal& sharedDescriptorData) : _device(device), _sharedDescriptorData(sharedDescriptorData),
	_descriptorSetLayouts(creationData.descriptorSetLayoutListInitialCapacity)
{
}

DeviceDescriptorDataInternal::~DeviceDescriptorDataInternal()
{
}

IDObject<AutoCleanupDescriptorSetLayout> DeviceDescriptorDataInternal::AddDescriptorSetLayout(std::uint32_t firstBinding,
	const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserve)
{
	std::vector<VkDescriptorSetLayoutBinding> bindingList;

	VkDescriptorSetLayout add = VK_NULL_HANDLE;
	VkDescriptorSetLayoutCreateInfo createInfo{};

	createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

	if (!descriptorSetLayoutBindings.empty())
	{
		bindingList = _sharedDescriptorData.GetDescriptorSetLayoutBindings(firstBinding, descriptorSetLayoutBindings);

		createInfo.bindingCount = static_cast<std::uint32_t>(bindingList.size());
		createInfo.pBindings = bindingList.data();
	}

	if (vkCreateDescriptorSetLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("DeviceDescriptorDataInternal::AddDescriptorSetLayout Error: Program failed to create ");

	return _descriptorSetLayouts.AddObject(AutoCleanupDescriptorSetLayout(_device, add), addOnReserve);
}
