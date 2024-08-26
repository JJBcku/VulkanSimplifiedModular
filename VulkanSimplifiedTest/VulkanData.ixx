export module VulkanData;

import std;
import VulkanData.Basic;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;
import VulkanData.SharedData;
import VulkanData.PipelineLayoutData;
import VulkanData.PipelinesList;
import VulkanData.RenderPassData;

export struct VulkanData
{
	std::unique_ptr<VulkanDataBasic> basicData;
	std::unique_ptr<VulkanDataInstanceDependent> instanceDependent;
	std::unique_ptr<VulkanDataDeviceDependent> deviceDependent;
	std::unique_ptr<VulkanSharedData> sharedData;
	std::unique_ptr<VulkanRenderPassData> renderPassData;
	std::unique_ptr<VulkanPipelineLayoutData> pipelineLayoutData;
	std::unique_ptr<VulkanDataPipelinesList> pipelinesList;

	VulkanData() = default;

	VulkanData(const VulkanData&) noexcept = delete;

	VulkanData& operator=(const VulkanData&) noexcept = delete;
};