module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.PhysicalDevice.Internal;

export class PhysicalDeviceInternal
{
public:
	PhysicalDeviceInternal(VkPhysicalDevice physicalDevice);
	~PhysicalDeviceInternal();

	PhysicalDeviceInternal(const PhysicalDeviceInternal&) noexcept = default;

	PhysicalDeviceInternal& operator=(const PhysicalDeviceInternal&) noexcept = default;

private:
	VkPhysicalDevice _physicalDevice;
};