export module VulkanData;

import std;
import VulkanData.Basic;

export struct VulkanData
{
	std::unique_ptr<VulkanDataBasic> basicData;

	VulkanData() = default;

	VulkanData(const VulkanData&) noexcept = delete;

	VulkanData& operator=(const VulkanData&) noexcept = delete;
};