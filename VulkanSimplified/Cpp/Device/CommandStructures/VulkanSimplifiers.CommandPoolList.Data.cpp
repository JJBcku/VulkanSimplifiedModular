module VulkanSimplifiers.CommandPoolQFGroupList.Data;

CommandBufferGenericID::CommandBufferGenericID()
{
	type = static_cast<CommandBufferIDType>(std::numeric_limits<std::uint64_t>::max());
}