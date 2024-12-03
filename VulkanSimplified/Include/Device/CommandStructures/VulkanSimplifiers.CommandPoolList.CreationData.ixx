export module VulkanSimplifiers.CommandPoolList.CreationData;

import std;

export import VulkanSimplifiers.CommandPoolQFGroupList.CreationData;

export struct CommandPoolListCreationData
{
	std::vector<CommandPoolQFGroupListCreationData> queueGroupCreationData;

	CommandPoolListCreationData();
};