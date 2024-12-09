module;

#include <vulkan/vulkan.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

module VulkanSimplifiers.Window.Internal;

WindowInternal::WindowInternal(WindowCreationData data, VkInstance instance, EventHandlingInternal& eventHandler) : _eventHandler(eventHandler)
{
	_width = static_cast<uint32_t>(data.windowWidth);
	_height = static_cast<uint32_t>(data.windowHeight);
	
	_window = nullptr;
	_windowID = std::numeric_limits<std::uint64_t>::max();
	_instance = VK_NULL_HANDLE;
	CreateWindow(data);

	_surface = VK_NULL_HANDLE;
	SetInstace(instance);

	_device = VK_NULL_HANDLE;
	_physicalDevice = VK_NULL_HANDLE;
	_swapchain = VK_NULL_HANDLE;

	_surfacePresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	_format = VK_FORMAT_UNDEFINED;
	_swapchainFlags = 0;
	_imageAmount = 0;

	_minimized = false;
	_hidden = false;
	_quit = false;
	_resized = false;

	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;

	_eventHandlingID = _eventHandler.RegisterWindowEventCallback(WindowInternal::HandleWindowEventStatic, this, 0);
}

WindowInternal::~WindowInternal()
{
	DestroyWindow();
}

WindowInternal::WindowInternal(WindowInternal&& other) : _eventHandler(other._eventHandler), _eventHandlingID(std::move(other._eventHandlingID)), _width(other._width),
_height(other._height), _window(other._window), _instance(other._instance), _surface(other._surface), _device(other._device), _physicalDevice(other._physicalDevice),
_swapchain(other._swapchain), _swapchainImages(std::move(other._swapchainImages)), _surfacePresentMode(other._surfacePresentMode), _format(other._format),
_swapchainFlags(other._swapchainFlags), _imageAmount(other._imageAmount), _queueFamilies(std::move(other._queueFamilies)),
_minimized(other._minimized), _hidden(other._hidden), _quit(other._quit), _resized(other._resized)
{
	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;

	other._width = 0;
	other._height = 0;
	other._window = nullptr;
	other._instance = VK_NULL_HANDLE;
	other._surface = VK_NULL_HANDLE;
	other._device = VK_NULL_HANDLE;
	other._physicalDevice = VK_NULL_HANDLE;
	other._swapchain = VK_NULL_HANDLE;
	other._surfacePresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	other._format = VK_FORMAT_UNDEFINED;
	other._swapchainFlags = 0;
	other._imageAmount = 0;
	other._minimized = false;
	other._hidden = false;
	other._quit = false;
	other._resized = false;
}

void WindowInternal::SetInstace(VkInstance instance)
{
	if (_instance != VK_NULL_HANDLE)
		throw std::runtime_error("WindowInternal::SetInstace Error: Program tried to set already set vulkan instance value!");

	_instance = instance;

	if (_instance != VK_NULL_HANDLE)
	{
		if (SDL_Vulkan_CreateSurface(_window, _instance, &_surface) != SDL_TRUE)
			throw std::runtime_error("WindowInternal::SetInstace Error: Program failed to create the window surface!");
	}
}

bool WindowInternal::IsClosingRequested() const
{
	return _quit;
}

bool WindowInternal::IsPaused() const
{
	return _minimized || _hidden;
}

bool WindowInternal::IsResized()
{
	bool ret = _resized;
	_resized = false;

	return ret;
}

std::uint32_t WindowInternal::GetWidth() const
{
	return _width;
}

std::uint32_t WindowInternal::GetHeight() const
{
	return _height;
}

SDL_Window* WindowInternal::GetWindow() const
{
	return _window;
}

VkSurfaceKHR WindowInternal::GetSurface() const
{
	return _surface;
}

VkSwapchainKHR WindowInternal::GetSwapchain() const
{
	return _swapchain;
}

VkImage WindowInternal::GetSwapchainImage(std::uint32_t imageIndex) const
{
	if (_swapchain == VK_NULL_HANDLE)
		throw std::runtime_error("WindowInternal::GetSwapchainImage Error: Program tried to get an image from a non-existent swapchain!");

	if (_swapchainImages.size() <= imageIndex)
		throw std::runtime_error("WindowInternal::GetSwapchainImage Error: Program tried to get read beyond swapchain images list!");

	return _swapchainImages[imageIndex];
}

void WindowInternal::CreateSwapchain(SwapchainInitData swapchainInit, bool throwOnSwapchainExist, bool throwOnDeviceChange)
{
	if (_swapchain != VK_NULL_HANDLE && throwOnSwapchainExist)
		throw std::runtime_error("WindowInternal::CreateSwapchain Error: Program tried to create an existing swapchain!");

	if (_device != VK_NULL_HANDLE && swapchainInit.device != _device)
	{
		if (throwOnDeviceChange)
			throw std::runtime_error("WindowInternal::CreateSwapchain Error: Program tried to create a swapchain using different device!");
		else
			DestroySwapchain();
	}

	_device = swapchainInit.device;
	_physicalDevice = swapchainInit.physicalDevice;
	_surfacePresentMode = swapchainInit.surfacePresentMode;
	_format = swapchainInit.format;
	_swapchainFlags = swapchainInit.flags;
	_imageAmount = swapchainInit.imageAmount;
	_queueFamilies = std::move(swapchainInit.queueFamilies);

	ReCreateSwapchain();
}

bool WindowInternal::AcquireNextImage(VkDevice device, std::uint64_t timeout, VkSemaphore semaphore, VkFence fence, std::uint32_t& returnIndex)
{
	if (device != _device)
		throw std::runtime_error("WindowInternal::AcquireNextImage Error: Program tried to used different device than swapchain was created with!");

	VkResult result = vkAcquireNextImageKHR(_device, _swapchain, timeout, semaphore, fence, &returnIndex);

	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("WindowInternal::AcquireNextImage Error: Program failed to acquire next image!");

	return result == VK_SUCCESS;
}

bool WindowInternal::HandleWindowEventStatic(const SDLModuleWindowEvent& event, void* windowptr)
{
	return static_cast<WindowInternal*>(windowptr)->HandleWindowEvent(event);
}

void WindowInternal::CreateWindow(WindowCreationData data)
{
	if (_window != nullptr)
		throw std::runtime_error("Error: Program tried to create an already existing window!");

	Uint32 flags = SDL_WINDOW_VULKAN;

	switch (data.properties)
	{
	case WindowProperties::NONE:
		break;
	case WindowProperties::RESIZABLE:
		flags |= SDL_WINDOW_RESIZABLE;
		break;
	case WindowProperties::BORDERLESS:
		flags |= SDL_WINDOW_BORDERLESS;
		break;
	case WindowProperties::FULLSCREEN:
		flags |= SDL_WINDOW_FULLSCREEN;
		break;
	case WindowProperties::FULSCREEN_BORDERLESS:
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS;
		break;
	default:
		throw std::runtime_error("Error: Unknown window creation properties!");
	}

	_window = SDL_CreateWindow(data.windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, data.windowWidth, data.windowHeight, flags);

	if (_window == nullptr)
		throw std::runtime_error("Error: Program failed to create a window!");

	_windowID = SDL_GetWindowID(_window);
}

void WindowInternal::DestroyWindow()
{
	if (_eventHandlingID.has_value())
	{
		_eventHandler.UnRegisterWindowEventCallback(_eventHandlingID.value(), true);
		_eventHandlingID.reset();
	}

	if (_surface != VK_NULL_HANDLE)
	{
		DestroySwapchain();

		vkDestroySurfaceKHR(_instance, _surface, nullptr);
		_surface = VK_NULL_HANDLE;
	}

	if (_window != nullptr)
	{
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}
}

void WindowInternal::ReCreateSwapchain()
{
	DestroySwapchain();

	VkSurfaceCapabilitiesKHR capabilities{};

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice, _surface, &capabilities);

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.flags = _swapchainFlags;
	createInfo.surface = _surface;
	createInfo.minImageCount = _imageAmount;
	createInfo.imageFormat = _format;
	createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	createInfo.imageExtent.width = capabilities.currentExtent.width;
	createInfo.imageExtent.height = capabilities.currentExtent.height;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;

	if (_queueFamilies.size() > 1)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(_queueFamilies.size());
		createInfo.pQueueFamilyIndices = _queueFamilies.data();
	}

	createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = _surfacePresentMode;
	createInfo.clipped = VK_TRUE;

	if (vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapchain) != VK_SUCCESS)
		throw std::runtime_error("Program failed to create the swapchain!");

	std::uint32_t imageCreated = 0;
	vkGetSwapchainImagesKHR(_device, _swapchain, &imageCreated, nullptr);
	_swapchainImages.resize(imageCreated);
	vkGetSwapchainImagesKHR(_device, _swapchain, &imageCreated, _swapchainImages.data());
}

void WindowInternal::DestroySwapchain()
{
	if (_swapchain != VK_NULL_HANDLE)
	{
		vkDeviceWaitIdle(_device);

		_swapchainImages.clear();

		vkDestroySwapchainKHR(_device, _swapchain, nullptr);
		_swapchain = VK_NULL_HANDLE;
	}
}

bool WindowInternal::HandleWindowEvent(const SDLModuleWindowEvent& event)
{
	if (event.windowID != _windowID)
		return true;

	switch (event.event)
	{
	case SDL_MODULE_WINDOWEVENT_SHOWN:
		_hidden = false;
		break;
	case SDL_MODULE_WINDOWEVENT_HIDDEN:
		_hidden = true;
		break;
	case SDL_MODULE_WINDOWEVENT_RESIZED:
		_width = static_cast<std::uint32_t>(event.data1);
		_height = static_cast<std::uint32_t>(event.data2);
		if (_swapchain != VK_NULL_HANDLE)
			ReCreateSwapchain();
		break;
	case SDL_MODULE_WINDOWEVENT_SIZE_CHANGED:
		_width = static_cast<std::uint32_t>(event.data1);
		_height = static_cast<std::uint32_t>(event.data2);
		if (_swapchain != VK_NULL_HANDLE)
			ReCreateSwapchain();
		break;
	case SDL_MODULE_WINDOWEVENT_MINIMIZED:
		_minimized = true;
		break;
	case SDL_MODULE_WINDOWEVENT_MAXIMIZED:
		_minimized = false;
		break;
	case SDL_MODULE_WINDOWEVENT_RESTORED:
		_minimized = false;
		break;
	case SDL_MODULE_WINDOWEVENT_CLOSE:
		_quit = true;
		break;
	default:
		break;
	}

	return false;
}
