module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.PhysicalDevice.Internal;

PhysicalDeviceInternal::PhysicalDeviceInternal(VkPhysicalDevice physicalDevice) : _physicalDevice(physicalDevice)
{
}

PhysicalDeviceInternal::~PhysicalDeviceInternal()
{
}
