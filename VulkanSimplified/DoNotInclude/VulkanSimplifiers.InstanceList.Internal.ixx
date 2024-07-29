module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.InstanceList.Internal;

import std;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.Instance.Internal;
import VulkanSimplifiers.Common.VulkanVersionData;

import VulkanSimplifiers.WindowList.Internal;

export typedef std::unique_ptr<InstanceInternal> InstancePointer;

export class InstanceListInternal
{
public:
	InstanceListInternal(size_t initialListCapacity, WindowListInternal& windowList);
	~InstanceListInternal();

	InstanceListInternal(const InstanceListInternal&) noexcept = delete;

	InstanceListInternal& operator=(const InstanceListInternal&) noexcept = delete;

	VulkanVersionData GetMaxAvailableVulkanVersion() const;

private:
	VulkanVersionData _maxApiVersion;
	UnsortedList<InstancePointer> _instanceList;

	std::vector<VkExtensionProperties> _availableExtensions;
	std::vector<VkLayerProperties> _availableLayer;

	WindowListInternal& _windowList;

	std::uint32_t FindMaximumAvailableVulkanVersion() const;
};