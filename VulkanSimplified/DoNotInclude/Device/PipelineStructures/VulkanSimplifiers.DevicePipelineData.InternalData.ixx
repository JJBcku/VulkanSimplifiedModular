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

	VkPipelineLayout GetPipelineLayout() const;

private:
	VkDevice _device;
	VkPipelineLayout _layout;

	void DestroyLayout();
};

export class AutoCleanupGraphicsPipeline
{
public:
	AutoCleanupGraphicsPipeline(VkDevice device, VkPipeline pipeline);
	~AutoCleanupGraphicsPipeline();

	AutoCleanupGraphicsPipeline(const AutoCleanupGraphicsPipeline&) noexcept = delete;
	AutoCleanupGraphicsPipeline(AutoCleanupGraphicsPipeline&& rhs) noexcept;

	AutoCleanupGraphicsPipeline& operator=(const AutoCleanupGraphicsPipeline&) noexcept = delete;
	AutoCleanupGraphicsPipeline& operator=(AutoCleanupGraphicsPipeline&& rhs) noexcept;

	VkPipeline GetPipeline() const;

private:
	VkDevice _device;
	VkPipeline _pipeline;

	void DestroyPipeline();
};