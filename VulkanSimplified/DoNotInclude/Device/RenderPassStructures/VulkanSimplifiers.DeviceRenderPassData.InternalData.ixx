module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DeviceRenderPassData.InternalData;

export class AutoCleanupRenderPass
{
public:
	AutoCleanupRenderPass(VkDevice device, VkRenderPass renderPass);
	~AutoCleanupRenderPass();

	AutoCleanupRenderPass(const AutoCleanupRenderPass&) noexcept = delete;
	AutoCleanupRenderPass(AutoCleanupRenderPass&& rhs) noexcept;

	AutoCleanupRenderPass& operator=(const AutoCleanupRenderPass&) noexcept = delete;
	AutoCleanupRenderPass& operator=(AutoCleanupRenderPass&& rhs) noexcept;

	VkRenderPass GetRenderPass() const;

private:
	VkDevice _device;
	VkRenderPass _renderPass;

	void DestroyRenderPass();
};