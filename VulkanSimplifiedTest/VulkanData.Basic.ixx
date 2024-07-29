export module VulkanData.Basic;

import std;

export import ListTemplates.IDObject;

import VulkanSimplifiers.Main;

import VulkanSimplifiers.WindowList.Data;

export struct VulkanDataBasic
{
	std::optional<MainSimplifier> main;
	IDObject<WindowPointer> windowID;

	VulkanDataBasic() = default;

	VulkanDataBasic(const VulkanDataBasic&) noexcept = delete;
	VulkanDataBasic(VulkanDataBasic&&) noexcept = delete;

	VulkanDataBasic& operator=(const VulkanDataBasic&) noexcept = delete;
	VulkanDataBasic& operator=(VulkanDataBasic&&) noexcept = delete;
};