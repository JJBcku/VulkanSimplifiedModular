module;

#include <vulkan/vulkan.hpp>
#include <SDL2/SDL_vulkan.h>

module VulkanSimplifiers.InstanceList.Internal;

InstanceListInternal::InstanceListInternal(size_t initialListCapacity, WindowListInternal& windowList) : _instanceList(initialListCapacity), _windowList(windowList)
{
	std::uint32_t data = FindMaximumAvailableVulkanVersion();
	_maxApiVersion = VulkanVersionData(data);

	data = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &data, nullptr);
	_availableExtensions.resize(data);

	vkEnumerateInstanceExtensionProperties(nullptr, &data, _availableExtensions.data());

	data = 0;
	vkEnumerateInstanceLayerProperties(&data, nullptr);
	_availableLayer.resize(data);

	vkEnumerateInstanceLayerProperties(&data, _availableLayer.data());
}

InstanceListInternal::~InstanceListInternal()
{
}

VulkanVersionData InstanceListInternal::GetMaxAvailableVulkanVersion() const
{
	return _maxApiVersion;
}

std::uint32_t InstanceListInternal::FindMaximumAvailableVulkanVersion() const
{
#pragma warning(push)
#pragma warning(disable : 4191)

	std::uint32_t ret = 0;
	auto func = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(NULL, "vkEnumerateInstanceVersion"));
#pragma warning(pop)

	if (func == NULL)
	{
		ret = VK_API_VERSION_1_0;
	}
	else
	{
		func(&ret);
	}

	return ret;
}