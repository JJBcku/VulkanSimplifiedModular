module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.WindowList.Internal;

import std;
import ListTemplates.IterativeUnsortedList;
import VulkanSimplifiers.Window.Internal;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.WindowList.Data;

import VulkanSimplifiers.EventHandling.Internal;
import VulkanSimplifiers.EventHandling.SDLModule.WindowEvent;

export class WindowListInternal
{
public:
	WindowListInternal(size_t initialListCapacity, EventHandlingInternal& eventHandler);
	~WindowListInternal();

	WindowListInternal(const WindowListInternal&) noexcept = delete;

	WindowListInternal& operator=(const WindowListInternal&) noexcept = delete;

	IDObject<WindowPointer> CreateWindow(WindowCreationData data, size_t addReserved);
	bool DeleteWindow(IDObject<WindowPointer> windowID, bool throwOnIDNotFound);
	void DeleteAll(size_t capacityAfterReserve = 0);

	void SetInstance(VkInstance instance);

	WindowInternal& GetWindowSimplifier(IDObject<WindowPointer> windowID);

	const WindowInternal& GetWindowSimplifier(IDObject<WindowPointer> windowID) const;

private:
	IterativeUnsortedList<WindowPointer> _windowList;
	VkInstance _instance;

	EventHandlingInternal& _eventHandler;
};