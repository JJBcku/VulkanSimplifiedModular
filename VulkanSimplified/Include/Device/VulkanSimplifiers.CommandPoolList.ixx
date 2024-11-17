export module VulkanSimplifiers.CommandPoolList;

import std;

import VulkanSimplifiers.CommandPoolList.Internal;

export class CommandPoolListSimplifier
{
public:
	CommandPoolListSimplifier(CommandPoolListInternal& ref);
	~CommandPoolListSimplifier();

	CommandPoolListSimplifier(const CommandPoolListSimplifier&) noexcept = delete;

	CommandPoolListSimplifier& operator= (const CommandPoolListSimplifier&) noexcept = delete;

private:
	CommandPoolListInternal& _internal;
};