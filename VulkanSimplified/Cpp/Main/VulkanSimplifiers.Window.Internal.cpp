module;

#include <vulkan/vulkan.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

module VulkanSimplifiers.Window.Internal;

WindowInternal::WindowInternal(WindowCreationData data, VkInstance instance)
{
	_width = static_cast<uint32_t>(data.windowWidth);
	_height = static_cast<uint32_t>(data.windowHeight);
	
	_window = nullptr;
	_instance = VK_NULL_HANDLE;
	CreateWindow(data);

	_surface = VK_NULL_HANDLE;
	SetInstace(instance);

	_minimized = false;
	_hidden = false;
	_quit = false;
	_resized = false;

	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;
}

WindowInternal::~WindowInternal()
{
	DestroyWindow();
}

WindowInternal::WindowInternal(WindowInternal&& other) : _window(other._window), _instance(other._instance), _surface(other._surface), _width(other._width), _height(other._height),
_minimized(other._minimized), _hidden(other._hidden), _quit(other._quit), _resized(other._resized)
{
	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;

	other._window = nullptr;
	other._instance = VK_NULL_HANDLE;
	other._surface = VK_NULL_HANDLE;
	other._width = 0;
	other._height = 0;
	other._minimized = false;
	other._hidden = false;
	other._quit = false;
	other._resized = false;
}

WindowInternal& WindowInternal::operator=(WindowInternal&& other)
{
	_window = other._window;
	_instance = other._instance;
	_surface = other._surface;
	_width = other._width;
	_height = other._height;
	_minimized = other._minimized;
	_hidden = other._hidden;
	_quit = other._quit;
	_resized = other._resized;
	_cpadding[0] = 0;
	_cpadding[1] = 0;
	_cpadding[2] = 0;
	_cpadding[3] = 0;

	other._window = nullptr;
	other._instance = VK_NULL_HANDLE;
	other._surface = VK_NULL_HANDLE;
	other._width = 0;
	other._height = 0;
	other._minimized = false;
	other._hidden = false;
	other._quit = false;
	other._resized = false;

	return *this;
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

bool WindowInternal::GetQuit() const
{
	return _quit;
}

bool WindowInternal::GetPaused() const
{
	return _minimized || _hidden;
}

bool WindowInternal::GetResized()
{
	bool ret = _resized;
	_resized = false;

	return ret;
}

SDL_Window* WindowInternal::GetWindow() const
{
	return _window;
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
}

void WindowInternal::DestroyWindow()
{
	if (_instance != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(_instance, _surface, nullptr);
		_surface = VK_NULL_HANDLE;
	}

	if (_window != nullptr)
	{
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}
}
