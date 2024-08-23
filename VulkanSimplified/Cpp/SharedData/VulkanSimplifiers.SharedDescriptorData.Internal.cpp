module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.SharedDescriptorData.Internal;

SharedDescriptorDataInternal::SharedDescriptorDataInternal(const SharedDescriptorDataCreationInfo& creationInfo) :
	_descriptorSetLayoutBindings(creationInfo.descriptorSetLayoutBindingsInitialCapacity)
{
}

SharedDescriptorDataInternal::~SharedDescriptorDataInternal()
{
}

IDObject<DescriptorSetLayoutBindingData> SharedDescriptorDataInternal::AddDescriptorSetLayoutBindingsData(std::uint32_t bindings, DescriptorTypeFlags descriptorType,
	std::uint32_t descriptorAmount, ShaderTypeFlags shaderStageFlags, size_t addOnReserve)
{
	DescriptorSetLayoutBindingData add;

	add.binding = bindings;

	switch (descriptorType)
	{
	case DescriptorTypeFlags::INPUT_ATTACHMENT:
		add.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
		break;
	case DescriptorTypeFlags::STORAGE_BUFFER_DYNAMIC:
		add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;;
		break;
	case DescriptorTypeFlags::UNIFORM_BUFFER_DYNAMIC:
		add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
		break;
	case DescriptorTypeFlags::STORAGE_BUFFER:
		add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		break;
	case DescriptorTypeFlags::UNIFORM_BUFFER:
		add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		break;
	case DescriptorTypeFlags::STORAGE_TEXEL_BUFFER:
		add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
		break;
	case DescriptorTypeFlags::UNIFORM_TEXEL_BUFFER:
		add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
		break;
	case DescriptorTypeFlags::STORAGE_IMAGE:
		add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		break;
	case DescriptorTypeFlags::SAMPLED_IMAGE:
		add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		break;
	case DescriptorTypeFlags::COMBINED_IMAGE_SAMPLER:
		add.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		break;
	case DescriptorTypeFlags::SAMPLER:
		add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
		break;
	default:
		std::runtime_error("SharedDescriptorDataInternal::AddDescriptorSetLayoutBindingsData Error: Program was given an erroneous descriptor type value!");
	}

	add.descriptorCount = descriptorAmount;

	add.shaderStages = 0;
	if ((shaderStageFlags & SHADER_TYPE_FRAGMENT) == SHADER_TYPE_FRAGMENT)
		add.shaderStages |= VK_SHADER_STAGE_FRAGMENT_BIT;

	if ((shaderStageFlags & SHADER_TYPE_VERTEX) == SHADER_TYPE_VERTEX)
		add.shaderStages |= VK_SHADER_STAGE_VERTEX_BIT;

	return _descriptorSetLayoutBindings.AddUniqueObject(std::move(add), addOnReserve);
}