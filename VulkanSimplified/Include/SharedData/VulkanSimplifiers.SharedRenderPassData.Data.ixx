export module VulkanSimplifiers.SharedRenderPassData.Data;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SharedRenderPassData.InternalData;

export struct RenderPassAttachmentData;
export struct RenderPassAttachmentReference;
export struct SubpassDependencyData;

export constexpr std::uint32_t externalSubpass = std::numeric_limits<std::uint32_t>::max();

export enum class RenderPassAttachmentLoadOP
{
	LOAD = 0x1,
	CLEAR = 0x2,
	IGNORE = 0x3,
};

export enum class RenderPassAttachmentStoreOP
{
	STORE = 0x1,
	IGNORE = 0x2,
};

export struct RenderPassDoubleColorClearValues;
export struct RenderPassInt64ColorClearValues;
export struct RenderPassUInt64ColorClearValues;
export struct RenderPassFloatColorClearValues;
export struct RenderPassIntColorClearValues;
export struct RenderPassUIntColorClearValues;
export struct RenderPassDepthStencilClearValues;

export enum class RenderPassClearValueIDType : std::uint64_t
{
	COLOR_DOUBLE = 0x1,
	COLOR_INT64 = 0x2,
	COLOR_UINT64 = 0x4,
	COLOR_FLOAT = 0x8,
	COLOR_INT = 0x10,
	COLOR_UINT = 0x20,
	DEPTH_STENCIL = 0x40,
};

export union RenderPassClearValuesID
{
	RenderPassClearValueIDType type;

	struct
	{
		RenderPassClearValueIDType type;
		IDObject<RenderPassDoubleColorClearValues> ID;
	} doubleColorID;

	struct
	{
		RenderPassClearValueIDType type;
		IDObject<RenderPassInt64ColorClearValues> ID;
	} int64ColorID;

	struct
	{
		RenderPassClearValueIDType type;
		IDObject<RenderPassUInt64ColorClearValues> ID;
	} uint64ColorID;

	struct
	{
		RenderPassClearValueIDType type;
		IDObject<RenderPassFloatColorClearValues> ID;
	} floatColorID;

	struct
	{
		RenderPassClearValueIDType type;
		IDObject<RenderPassIntColorClearValues> ID;
	} intColorID;

	struct
	{
		RenderPassClearValueIDType type;
		IDObject<RenderPassUIntColorClearValues> ID;
	} uintColorID;

	struct
	{
		RenderPassClearValueIDType type;
		IDObject<RenderPassDepthStencilClearValues> ID;
	} depthStencilID;

	RenderPassClearValuesID();
	RenderPassClearValuesID(IDObject<RenderPassDoubleColorClearValues> ID);
	RenderPassClearValuesID(IDObject<RenderPassInt64ColorClearValues> ID);
	RenderPassClearValuesID(IDObject<RenderPassUInt64ColorClearValues> ID);

	RenderPassClearValuesID(IDObject<RenderPassFloatColorClearValues> ID);
	RenderPassClearValuesID(IDObject<RenderPassIntColorClearValues> ID);
	RenderPassClearValuesID(IDObject<RenderPassUIntColorClearValues> ID);

	RenderPassClearValuesID(IDObject<RenderPassDepthStencilClearValues> ID);
};
