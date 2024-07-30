module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Instance.Internal;

import std;

import VulkanSimplifiers.Instance.Data;
import VulkanSimplifiers.DebugCallback;

export class InstanceInternal
{
public:
	InstanceInternal(const InstanceInitInfo& initInfo);
	~InstanceInternal();

private:
	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debugMessenger;
};