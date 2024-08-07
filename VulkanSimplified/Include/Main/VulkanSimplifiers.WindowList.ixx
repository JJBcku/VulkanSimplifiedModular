export module VulkanSimplifiers.WindowList;

import std;
import ListTemplates.IDObject;
import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.Window;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.WindowList.Data;

export class WindowListSimplifier
{
public:
	WindowListSimplifier(WindowListInternal& ref);
	~WindowListSimplifier();

	WindowListSimplifier& operator=(const WindowListSimplifier&) noexcept = delete;

	IDObject<WindowPointer> CreateWindow(WindowCreationData data, size_t addOnReservation = 0);
	bool DeleteWindow(IDObject<WindowPointer> windowID, bool throwOnIDNotFound = true);
	void DeleteAll(size_t capacityAfterReserve = 0);

	WindowSimplifier GetWindowSimplifier(IDObject<WindowPointer> windowID);

	const WindowSimplifier GetWindowSimplifier(IDObject<WindowPointer> windowID) const;

private:
	WindowListInternal& _internal;
};