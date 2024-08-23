module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DeviceDescriptorData.InternalData;

AutoCleanupDescriptorSetLayout::AutoCleanupDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout) : _device(device), _descriptorSetLayout(descriptorSetLayout)
{
}

AutoCleanupDescriptorSetLayout::~AutoCleanupDescriptorSetLayout()
{
	DestroyLayout();
}

AutoCleanupDescriptorSetLayout::AutoCleanupDescriptorSetLayout(AutoCleanupDescriptorSetLayout&& rhs) noexcept : _device(rhs._device), _descriptorSetLayout(rhs._descriptorSetLayout)
{
	rhs._device = VK_NULL_HANDLE;
	rhs._descriptorSetLayout = VK_NULL_HANDLE;
}

AutoCleanupDescriptorSetLayout& AutoCleanupDescriptorSetLayout::operator=(AutoCleanupDescriptorSetLayout&& rhs) noexcept
{
	DestroyLayout();

	_device = rhs._device;
	_descriptorSetLayout = rhs._descriptorSetLayout;

	rhs._device = VK_NULL_HANDLE;
	rhs._descriptorSetLayout = VK_NULL_HANDLE;

	return *this;
}

VkDescriptorSetLayout AutoCleanupDescriptorSetLayout::GetDescriptorSetLayout() const
{
	return _descriptorSetLayout;
}

void AutoCleanupDescriptorSetLayout::DestroyLayout()
{
	if (_descriptorSetLayout != VK_NULL_HANDLE)
	{
		vkDestroyDescriptorSetLayout(_device, _descriptorSetLayout, nullptr);
		_descriptorSetLayout = VK_NULL_HANDLE;
	}
}
