module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DeviceRenderPassData.InternalData;

AutoCleanupRenderPass::AutoCleanupRenderPass(VkDevice device, VkRenderPass renderPass) : _device(device), _renderPass(renderPass)
{
}

AutoCleanupRenderPass::~AutoCleanupRenderPass()
{
	DestroyRenderPass();
}

AutoCleanupRenderPass::AutoCleanupRenderPass(AutoCleanupRenderPass&& rhs) noexcept : _device(rhs._device), _renderPass(rhs._renderPass)
{
	rhs._device = VK_NULL_HANDLE;
	rhs._renderPass = VK_NULL_HANDLE;
}

AutoCleanupRenderPass& AutoCleanupRenderPass::operator=(AutoCleanupRenderPass&& rhs) noexcept
{
	DestroyRenderPass();
	_device = rhs._device;
	_renderPass = rhs._renderPass;

	rhs._device = VK_NULL_HANDLE;
	rhs._renderPass = VK_NULL_HANDLE;

	return *this;
}

VkRenderPass AutoCleanupRenderPass::GetRenderPass() const
{
	return _renderPass;
}

void AutoCleanupRenderPass::DestroyRenderPass()
{
	if (_renderPass != VK_NULL_HANDLE)
	{
		vkDestroyRenderPass(_device, _renderPass, nullptr);
		_renderPass = VK_NULL_HANDLE;
	}
}
