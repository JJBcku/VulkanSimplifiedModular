module;

#include <SDL2/SDL.h>
#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.Main.Internal;

MainInternal::MainInternal(const MainSimplifierInitData& initData) : _eventHandler(initData.eventHandlerData), _windowList(initData.windowsListInitialCapacity)
{
	int result = SDL_Init(SDL_INIT_VIDEO);
	 if (result < 0)
		throw std::runtime_error("Program failed to initialize SDL, error code" + std::to_string(result));

	 _appTitle = initData.appTitle;
	 _appVariantTitle = initData.appVariantTitle;
	 _appVersion = initData.appVersion;
	 _engineName = initData.engineName;
	 _engineVersion = initData.engineVersion;

	 std::uint32_t data = FindMaximumAvailableVulkanVersion();
	 _maxApiVersion = VulkanVersionData(data);

	 std::vector<VkExtensionProperties> availableExtensions;
	 std::vector<VkLayerProperties> availableLayers;

	 data = 0;
	 vkEnumerateInstanceExtensionProperties(nullptr, &data, nullptr);
	 availableExtensions.resize(data);

	 vkEnumerateInstanceExtensionProperties(nullptr, &data, availableExtensions.data());

	 data = 0;
	 vkEnumerateInstanceLayerProperties(&data, nullptr);
	 availableLayers.resize(data);

	 vkEnumerateInstanceLayerProperties(&data, availableLayers.data());

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	 bool found = false;
	 for (auto& extension : availableExtensions)
	 {
		 if (std::strcmp(extension.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0)
		 {
			 found = true;
			 break;
		 }
	 }

	 if (!found)
		 throw std::runtime_error("Error: Program does not found required debugging extensions!");

	 found = false;
	 for (auto& layer : availableLayers)
	 {
		 if (std::strcmp(layer.layerName, "VK_LAYER_KHRONOS_validation") == 0)
		 {
			 found = true;
			 break;
		 }
	 }

	 if (!found)
		 throw std::runtime_error("Error: Program does not found required debugging layers!");
#endif

	 _availableExtensions = CompileAvailableExtensionList(availableExtensions);
}

MainInternal::~MainInternal()
{
	SDL_Quit();
}

VulkanVersionData MainInternal::GetAppVersion() const
{
	return _appVersion;
}

EventHandlingInternal& MainInternal::GetEventHandler()
{
	return _eventHandler;
}

InstanceInternal& MainInternal::GetInstanceSimplifier()
{
	return *_instance;
}

WindowListInternal& MainInternal::GetWindowListSimplifier()
{
	return _windowList;
}

const EventHandlingInternal& MainInternal::GetEventHandler() const
{
	return _eventHandler;
}

const InstanceInternal& MainInternal::GetInstanceSimplifier() const
{
	return *_instance;
}

const WindowListInternal& MainInternal::GetWindowListSimplifier() const
{
	return _windowList;
}

VulkanVersionData MainInternal::GetMaxAvailableVulkanVersion() const
{
	return _maxApiVersion;
}

InstanceExtensionList MainInternal::GetAvailableInstanceExtensions() const
{
	return _availableExtensions;
}

std::uint32_t MainInternal::FindMaximumAvailableVulkanVersion() const
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

InstanceExtensionList MainInternal::CompileAvailableExtensionList(const std::vector<VkExtensionProperties>& extensions) const
{
	InstanceExtensionList ret = 0;

	for (auto& extension : extensions)
	{
		if (std::strcmp(extension.extensionName, VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME) == 0)
			ret |= SWAPCHAIN_EXTENDED_COLORSPACE;
	}

	return ret;
}
