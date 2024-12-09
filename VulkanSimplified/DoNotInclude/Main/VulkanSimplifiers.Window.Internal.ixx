module;

#include <vulkan/vulkan.hpp>
#include <SDL2/SDL.h>

export module VulkanSimplifiers.Window.Internal;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.InternalData;

import VulkanSimplifiers.EventHandling.Internal;
import VulkanSimplifiers.EventHandling.SDLModule.WindowEvent;

export class WindowInternal
{
public:
	WindowInternal(WindowCreationData data, VkInstance instance, EventHandlingInternal& eventHandler);
	~WindowInternal();

	WindowInternal(const WindowInternal&) = delete;
	WindowInternal(WindowInternal&& other);

	WindowInternal& operator=(const WindowInternal&) = delete;
	WindowInternal& operator=(WindowInternal&& other) = delete;

	void SetInstace(VkInstance instance);

	bool IsClosingRequested() const;
	bool IsPaused() const;
	bool IsResized();

	std::uint32_t GetWidth() const;
	std::uint32_t GetHeight() const;

	SDL_Window* GetWindow() const;
	VkSurfaceKHR GetSurface() const;
	VkSwapchainKHR GetSwapchain() const;

	VkImage GetSwapchainImage(std::uint32_t imageIndex) const;

	void CreateSwapchain(SwapchainInitData swapchainInit, bool throwOnSwapchainExist, bool throwOnDeviceChange);

	bool AcquireNextImage(VkDevice device, std::uint64_t timeout, VkSemaphore semaphore, VkFence fence, std::uint32_t& returnIndex);

	static bool HandleWindowEventStatic(const SDLModuleWindowEvent& event, void* windowptr);

private:
	EventHandlingInternal& _eventHandler;
	std::optional<IDObject<std::pair<WindowEventFunction, void*>>> _eventHandlingID;

	std::uint32_t _width, _height;

	SDL_Window* _window;
	std::uint64_t _windowID;

	VkInstance _instance;

	VkSurfaceKHR _surface;

	VkDevice _device;
	VkPhysicalDevice _physicalDevice;
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

	bool HandleWindowEvent(const SDLModuleWindowEvent& event);
};
