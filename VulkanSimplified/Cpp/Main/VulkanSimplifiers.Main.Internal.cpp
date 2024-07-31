module;

#include <vulkan/vulkan.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

module VulkanSimplifiers.Main.Internal;

MainInternal::MainInternal(const MainSimplifierInitData& initData) : _eventHandler(initData.eventHandlerData), _windowList(initData.windowsListInitialCapacity)
{
	int result = SDL_InitSubSystem(SDL_INIT_VIDEO);

	 if (result < 0)
		throw std::runtime_error("Program failed to initialize SDL, error code" + std::to_string(result));

	 _appName = initData.appName;
	 _appVariantName = initData.appVariantName;
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
	_windowList.DeleteAll(1);
	_instance.reset();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
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
	if (!_instance.has_value())
		throw std::runtime_error("MainInternal::GetInstanceSimplifier Error: Program tried to get a non-existent instance!");

	return _instance.value();
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
	if (!_instance.has_value())
		throw std::runtime_error("MainInternal::GetInstanceSimplifier const Error: Program tried to get a non-existent instance!");

	return _instance.value();
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

void MainInternal::CreateIntance(const InstanceCreationInfo& instanceInfo)
{
	if (_instance.has_value())
		throw std::runtime_error("MainInternal::CreateIntance Error: Program tried to create an already existing vulkan instance!");

	InstanceInitInfo initInfo;

	initInfo.appName = _appName;
	initInfo.appVersion = _appVersion.GetVulkanApiCompatibleVersion();
	initInfo.engineName = _engineName;
	initInfo.engineVersion = _engineVersion.GetVulkanApiCompatibleVersion();
	initInfo.usedVulkanApiVersion = instanceInfo.usedVulkanApiVersion.GetVulkanApiCompatibleVersion();
	initInfo.requestedExtensions = CompileRequestedExtensionsList(instanceInfo.requestedExtensions, instanceInfo.windowExampleID);
	initInfo.requestedLayers = CompileRequestedLayersList();
	initInfo.logicalDeviceListInitialCapacity = instanceInfo.logicalDeviceListInitialCapacity;

	_instance.emplace(initInfo);
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

std::vector<const char*> MainInternal::CompileRequestedExtensionsList(InstanceExtensionList requestedExtensions, const std::optional<IDObject<WindowPointer>>& windowID) const
{
	std::vector<const char*> ret;

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	ret.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

	std::vector<const char*> sdlRequired;

	if (windowID.has_value())
	{
		std::uint32_t size = 0;
		SDL_Vulkan_GetInstanceExtensions(nullptr, &size, nullptr);

		SDL_Vulkan_GetInstanceExtensions(nullptr, &size, sdlRequired.data());
	}

	ret.reserve(ret.size() + sdlRequired.size() + sizeof(requestedExtensions) * 8);

	if (!sdlRequired.empty())
	{
		ret.insert(ret.end(), sdlRequired.begin(), sdlRequired.end());
	}

	if ((requestedExtensions & _availableExtensions) != requestedExtensions)
		throw std::runtime_error("CompileRequestedExtensionsList Error: Program tried to create instance with an unavailable extension!");

	if ((requestedExtensions & SWAPCHAIN_EXTENDED_COLORSPACE) == SWAPCHAIN_EXTENDED_COLORSPACE)
		ret.push_back(VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME);

	return ret;
}

std::vector<const char*> MainInternal::CompileRequestedLayersList() const
{
	std::vector<const char*> ret;

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	ret.push_back("VK_LAYER_KHRONOS_validation");
#endif

	return ret;
}
