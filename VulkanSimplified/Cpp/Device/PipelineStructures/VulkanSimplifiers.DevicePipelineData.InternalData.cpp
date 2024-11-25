module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.DevicePipelineData.InternalData;

AutoCleanupPipelineLayout::AutoCleanupPipelineLayout(VkDevice device, VkPipelineLayout layout) : _device(device), _layout(layout)
{
}

AutoCleanupPipelineLayout::~AutoCleanupPipelineLayout()
{
	DestroyLayout();
}

AutoCleanupPipelineLayout::AutoCleanupPipelineLayout(AutoCleanupPipelineLayout&& rhs) noexcept : _device(rhs._device), _layout(rhs._layout)
{
	rhs._device = VK_NULL_HANDLE;
	rhs._layout = VK_NULL_HANDLE;
}

AutoCleanupPipelineLayout& AutoCleanupPipelineLayout::operator=(AutoCleanupPipelineLayout&& rhs) noexcept
{
	DestroyLayout();

	_device = rhs._device;
	_layout = rhs._layout;

	rhs._device = VK_NULL_HANDLE;
	rhs._layout = VK_NULL_HANDLE;

	return *this;
}

VkPipelineLayout AutoCleanupPipelineLayout::GetPipelineLayout() const
{
	return _layout;
}

void AutoCleanupPipelineLayout::DestroyLayout()
{
	if (_layout != VK_NULL_HANDLE)
	{
		vkDestroyPipelineLayout(_device, _layout, nullptr);
		_layout = VK_NULL_HANDLE;
	}
}

AutoCleanupGraphicsPipeline::AutoCleanupGraphicsPipeline(VkDevice device, VkPipeline pipeline) : _device(device), _pipeline(pipeline)
{
}

AutoCleanupGraphicsPipeline::~AutoCleanupGraphicsPipeline()
{
	DestroyPipeline();
}

AutoCleanupGraphicsPipeline::AutoCleanupGraphicsPipeline(AutoCleanupGraphicsPipeline&& rhs) noexcept : _device(rhs._device), _pipeline(rhs._pipeline)
{
	rhs._device = VK_NULL_HANDLE;
	rhs._pipeline = VK_NULL_HANDLE;
}

AutoCleanupGraphicsPipeline& AutoCleanupGraphicsPipeline::operator=(AutoCleanupGraphicsPipeline&& rhs) noexcept
{
	DestroyPipeline();
	_device = rhs._device;
	_pipeline = rhs._pipeline;

	rhs._device = VK_NULL_HANDLE;
	rhs._pipeline = VK_NULL_HANDLE;
	return *this;
}

VkPipeline AutoCleanupGraphicsPipeline::GetPipeline() const
{
	return _pipeline;
}

void AutoCleanupGraphicsPipeline::DestroyPipeline()
{
	if (_pipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(_device, _pipeline, nullptr);
		_pipeline = VK_NULL_HANDLE;
	}
}