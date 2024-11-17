export module VulkanSimplifiers.CommandPoolList.Internal;

import std;

import VulkanSimplifiers.CommandPoolList.CreationData;

export class CommandPoolListInternal
{
public:
	CommandPoolListInternal(const CommandPoolListCreationData& creationData);
	~CommandPoolListInternal();

private:
	std::int64_t stump;
};