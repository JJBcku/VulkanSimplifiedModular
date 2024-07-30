export module VulkanSimplifiers.WindowList.Internal;

import std;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.Window.Internal;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.WindowList.Data;

export class WindowListInternal
{
public:
	WindowListInternal(size_t initialListCapacity);
	~WindowListInternal();

	WindowListInternal(const WindowListInternal&) noexcept = delete;

	WindowListInternal& operator=(const WindowListInternal&) noexcept = delete;

	IDObject<WindowPointer> CreateWindow(WindowCreationData data, size_t addReserved);
	void DeleteAll(size_t capacityAfterReserve);

	WindowInternal& GetWindowSimplifier(IDObject<WindowPointer> windowID);

	const WindowInternal& GetWindowSimplifier(IDObject<WindowPointer> windowID) const;

private:
	UnsortedList<WindowPointer> _windowList;
};