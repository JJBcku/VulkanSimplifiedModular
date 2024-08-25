module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DevicePipelineData.Internal;

DevicePipelineDataInternal::DevicePipelineDataInternal(const DevicePipelineDataCreationData& creationInfo, const SharedPipelineDataInternal& pipelineData,
	const DeviceDescriptorDataInternal& descriptorData, VkDevice device) : _pipelineData(pipelineData), _descriptorData(descriptorData), _device(device),
	_pipelineLayouts(creationInfo.pipelineLayoutListInitialCapacity)
{
}

DevicePipelineDataInternal::~DevicePipelineDataInternal()
{
}

IDObject<AutoCleanupPipelineLayout> DevicePipelineDataInternal::AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserve)
{
	VkPipelineLayout add = VK_NULL_HANDLE;
	VkPipelineLayoutCreateInfo createInfo{};

	auto descriptorLayouts = _descriptorData.GetDescriptorSetLayouts(creationData._descriptorSets);
	auto pushConstants = _pipelineData.GetPushConstantData(creationData._pushConstants);

	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

	if (!descriptorLayouts.empty())
	{
		createInfo.setLayoutCount = static_cast<std::uint32_t>(descriptorLayouts.size());
		createInfo.pSetLayouts = descriptorLayouts.data();
	}

	if (!pushConstants.empty())
	{
		createInfo.pushConstantRangeCount = static_cast<std::uint32_t>(pushConstants.size());
		createInfo.pPushConstantRanges = pushConstants.data();
	}

	if (vkCreatePipelineLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
		throw std::runtime_error("DevicePipelineDataInternal::AddPipelineLayout Error: Program failed to create the pipeline layout!");

	return _pipelineLayouts.AddObject(AutoCleanupPipelineLayout(_device, add), addOnReserve);
}
