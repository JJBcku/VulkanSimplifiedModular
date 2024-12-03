export module VulkanSimplifiers.CommandPoolList;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.CommandPoolList.Internal;
import VulkanSimplifiers.CommandPoolQFGroupList.Data;
import VulkanSimplifiers.CommandPoolQFGroupList.Internal;
import VulkanSimplifiers.CommandPoolQFGroupList;

export class CommandPoolListSimplifier
{
public:
	CommandPoolListSimplifier(CommandPoolListInternal& ref);
	~CommandPoolListSimplifier();

	CommandPoolListSimplifier(const CommandPoolListSimplifier&) noexcept = delete;

	CommandPoolListSimplifier& operator= (const CommandPoolListSimplifier&) noexcept = delete;

	CommandPoolQFGroupListSimplifier GetCommandPoolQFGroupListSimplifier(size_t queuesID);

	const CommandPoolQFGroupListSimplifier GetCommandPoolQFGroupListSimplifier(size_t queuesID) const;

private:
	CommandPoolListInternal& _internal;
};