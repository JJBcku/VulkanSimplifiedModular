module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.DebugCallback;

import std;

export VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
	void*);