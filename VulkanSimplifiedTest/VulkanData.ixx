export module VulkanData;

import std;
import VulkanData.Basic;
import VulkanData.InstanceDependent;

export struct VulkanData
{
	std::unique_ptr<VulkanDataBasic> basicData;
	std::unique_ptr<VulkanDataInstanceDependent> instanceDependent;

	VulkanData() = default;

	VulkanData(const VulkanData&) noexcept = delete;

	VulkanData& operator=(const VulkanData&) noexcept = delete;
};