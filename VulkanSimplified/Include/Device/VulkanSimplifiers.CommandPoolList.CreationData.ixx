export module VulkanSimplifiers.CommandPoolList.CreationData;

import std;

export struct CommandPoolListCreationData
{
	size_t noIndividualResetCommandPoolListInitialReservation;
	size_t individualResetCommandPoolListInitialReservation;

	CommandPoolListCreationData();
};