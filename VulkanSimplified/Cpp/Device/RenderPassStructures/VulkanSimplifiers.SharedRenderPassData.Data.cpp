module VulkanSimplifiers.SharedRenderPassData.Data;

RenderPassClearValuesID::RenderPassClearValuesID()
{
	type = static_cast<RenderPassClearValueIDType>(std::numeric_limits<std::uint64_t>::max());
}

RenderPassClearValuesID::RenderPassClearValuesID(IDObject<RenderPassDoubleColorClearValues> ID)
{
	doubleColorID.type = RenderPassClearValueIDType::COLOR_DOUBLE;
	doubleColorID.ID = ID;
}

RenderPassClearValuesID::RenderPassClearValuesID(IDObject<RenderPassInt64ColorClearValues> ID)
{
	int64ColorID.type = RenderPassClearValueIDType::COLOR_INT64;
	int64ColorID.ID = ID;
}

RenderPassClearValuesID::RenderPassClearValuesID(IDObject<RenderPassUInt64ColorClearValues> ID)
{
	uint64ColorID.type = RenderPassClearValueIDType::COLOR_UINT64;
	uint64ColorID.ID = ID;
}

RenderPassClearValuesID::RenderPassClearValuesID(IDObject<RenderPassFloatColorClearValues> ID)
{
	floatColorID.type = RenderPassClearValueIDType::COLOR_FLOAT;
	floatColorID.ID = ID;
}

RenderPassClearValuesID::RenderPassClearValuesID(IDObject<RenderPassIntColorClearValues> ID)
{
	intColorID.type = RenderPassClearValueIDType::COLOR_INT;
	intColorID.ID = ID;
}

RenderPassClearValuesID::RenderPassClearValuesID(IDObject<RenderPassUIntColorClearValues> ID)
{
	uintColorID.type = RenderPassClearValueIDType::COLOR_UINT;
	uintColorID.ID = ID;
}

RenderPassClearValuesID::RenderPassClearValuesID(IDObject<RenderPassDepthStencilClearValues> ID)
{
	depthStencilID.type = RenderPassClearValueIDType::DEPTH_STENCIL;
	depthStencilID.ID = ID;
}