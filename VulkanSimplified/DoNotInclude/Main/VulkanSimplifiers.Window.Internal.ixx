module;

#include <vulkan/vulkan.hpp>
#include <SDL2/SDL.h>

export module VulkanSimplifiers.Window.Internal;

import std;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.InternalData;

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
	bool GetResized() const;

	std::uint32_t GetWidth() const;
	std::uint32_t GetHeight() const;

	SDL_Window* GetWindow() const;
	VkSurfaceKHR GetSurface() const;

	void CreateSwapchain(SwapchainInitData swapchainInit, bool throwOnSwapchainExist, bool throwOnDeviceChange);

private:
	std::uint32_t _width, _height;

	SDL_Window* _window;
	VkInstance _instance;

	VkSurfaceKHR _surface;

	VkDevice _device;
	VkSwapchainKHR _swapchain;

	std::vector<VkImage> _swapchainImages;

	VkPresentModeKHR _surfacePresentMode;
	VkFormat _format;
	VkSwapchainCreateFlagsKHR _swapchainFlags;
	std::uint32_t _imageAmount;

	std::vector<std::uint32_t> _queueFamilies;

	bool _minimized, _hidden, _quit, _resized;

	char _cpadding[4];

	void CreateWindow(WindowCreationData data);
	void DestroyWindow();

	void ReCreateSwapchain();
	void DestroySwapchain();
};
