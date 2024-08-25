module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DevicePipelineData.InternalData;

export class AutoCleanupPipelineLayout
{
public:
	AutoCleanupPipelineLayout(VkDevice device, VkPipelineLayout layout);
	~AutoCleanupPipelineLayout();

	AutoCleanupPipelineLayout(const AutoCleanupPipelineLayout&) noexcept = delete;
	AutoCleanupPipelineLayout(AutoCleanupPipelineLayout&& rhs) noexcept;

	AutoCleanupPipelineLayout& operator=(const AutoCleanupPipelineLayout&) noexcept = delete;
	AutoCleanupPipelineLayout& operator=(AutoCleanupPipelineLayout&& rhs) noexcept;

private:
	VkDevice _device;
	VkPipelineLayout _layout;

	void DestroyLayout();
};