module;

#include <SDL2/SDL.h>
#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.Window.Internal;

import VulkanSimplifiers.Window.Data;
import std;

export class WindowInternal
{
public:
	WindowInternal(WindowCreationData data, VkInstance instance);
	~WindowInternal();

	WindowInternal(const WindowInternal&) = delete;
	WindowInternal(WindowInternal&& other);

	WindowInternal& operator=(const WindowInternal&) = delete;
	WindowInternal& operator=(WindowInternal&& other);

	void SetInstace(VkInstance instance);

	bool GetQuit() const;
	bool GetPaused() const;
	bool GetResized();

	SDL_Window* GetWindow() const;

private:
	SDL_Window* _window;
	VkInstance _instance;

	VkSurfaceKHR _surface;

	std::uint32_t _width, _height;

	bool _minimized, _hidden, _quit, _resized;

	char _cpadding[4];

	void CreateWindow(WindowCreationData data);
	void DestroyWindow();
};
