export module VulkanData;

import std;
import VulkanData.Basic;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;

export struct VulkanData
{
	std::unique_ptr<VulkanDataBasic> basicData;
	std::unique_ptr<VulkanDataInstanceDependent> instanceDependent;
	std::unique_ptr<VulkanDataDeviceDependent> deviceDependent;

	VulkanData() = default;

	VulkanData(const VulkanData&) noexcept = delete;

	VulkanData& operator=(const VulkanData&) noexcept = delete;
};