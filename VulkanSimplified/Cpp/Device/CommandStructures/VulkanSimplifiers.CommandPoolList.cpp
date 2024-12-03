module VulkanSimplifiers.CommandPoolList;

CommandPoolListSimplifier::CommandPoolListSimplifier(CommandPoolListInternal& ref) : _internal(ref)
{
}

CommandPoolListSimplifier::~CommandPoolListSimplifier()
{
}

CommandPoolQFGroupListSimplifier CommandPoolListSimplifier::GetCommandPoolQFGroupListSimplifier(size_t queuesID)
{
	return _internal.GetCommandPoolQFGroupListSimplifier(queuesID);
}

const CommandPoolQFGroupListSimplifier CommandPoolListSimplifier::GetCommandPoolQFGroupListSimplifier(size_t queuesID) const
{
	return _internal.GetCommandPoolQFGroupListSimplifier(queuesID);
}