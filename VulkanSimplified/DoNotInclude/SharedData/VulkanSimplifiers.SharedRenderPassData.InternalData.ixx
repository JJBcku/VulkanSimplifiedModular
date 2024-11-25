module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SharedRenderPassData.InternalData;

import std;
export import ListTemplates.IDObject;

export struct RenderPassAttachmentData
{
	VkFormat format;
	VkSampleCountFlagBits samples;
	VkAttachmentLoadOp loadOP;
	VkAttachmentStoreOp storeOP;
	VkImageLayout initialLayout;
	VkImageLayout finalLayout;

	RenderPassAttachmentData();

	bool operator==(const RenderPassAttachmentData&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassAttachmentData&) const noexcept = default;
};

export struct RenderPassAttachmentReference
{
	std::uint32_t attachmentIndex;
	VkImageLayout attachmentLayout;

	RenderPassAttachmentReference();

	bool operator==(const RenderPassAttachmentReference&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassAttachmentReference&) const noexcept = default;
};

export struct SubpassDependencyData
{
	std::uint32_t srcSubpass;
	std::uint32_t dstSubpass;
	VkPipelineStageFlags srcStageFlags;
	VkPipelineStageFlags dstStageFlags;
	VkAccessFlags srcAccessFlags;
	VkAccessFlags dstAccessFlags;

	SubpassDependencyData();

	bool operator==(const SubpassDependencyData&) const noexcept = default;
	std::strong_ordering operator<=>(const SubpassDependencyData&) const noexcept = default;
};

export struct RenderPassDoubleColorClearValues
{
	double r;
	double g;
	double b;
	double a;

	RenderPassDoubleColorClearValues() = default;

	bool operator==(const RenderPassDoubleColorClearValues&) const noexcept = default;
	std::partial_ordering operator<=>(const RenderPassDoubleColorClearValues&) const noexcept = default;
};

export struct RenderPassInt64ColorClearValues
{
	std::int64_t r;
	std::int64_t g;
	std::int64_t b;
	std::int64_t a;

	RenderPassInt64ColorClearValues() = default;

	bool operator==(const RenderPassInt64ColorClearValues&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassInt64ColorClearValues&) const noexcept = default;
};

export struct RenderPassUInt64ColorClearValues
{
	std::uint64_t r;
	std::uint64_t g;
	std::uint64_t b;
	std::uint64_t a;

	RenderPassUInt64ColorClearValues() = default;

	bool operator==(const RenderPassUInt64ColorClearValues&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassUInt64ColorClearValues&) const noexcept = default;
};

export struct RenderPassFloatColorClearValues
{
	float r;
	float g;
	float b;
	float a;

	RenderPassFloatColorClearValues() = default;

	bool operator==(const RenderPassFloatColorClearValues&) const noexcept = default;
	std::partial_ordering operator<=>(const RenderPassFloatColorClearValues&) const noexcept = default;
};

export struct RenderPassIntColorClearValues
{
	std::int32_t r;
	std::int32_t g;
	std::int32_t b;
	std::int32_t a;

	RenderPassIntColorClearValues() = default;

	bool operator==(const RenderPassIntColorClearValues&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassIntColorClearValues&) const noexcept = default;
};

export struct RenderPassUIntColorClearValues
{
	std::uint32_t r;
	std::uint32_t g;
	std::uint32_t b;
	std::uint32_t a;

	RenderPassUIntColorClearValues() = default;

	bool operator==(const RenderPassUIntColorClearValues&) const noexcept = default;
	std::strong_ordering operator<=>(const RenderPassUIntColorClearValues&) const noexcept = default;
};

export struct RenderPassDepthStencilClearValues
{
	float d;
	std::uint32_t s;

	RenderPassDepthStencilClearValues() = default;

	bool operator==(const RenderPassDepthStencilClearValues&) const noexcept = default;
	std::partial_ordering operator<=>(const RenderPassDepthStencilClearValues&) const noexcept = default;
};