module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.WindowList.Internal;

WindowListInternal::WindowListInternal(size_t initialListCapacity) : _windowList(initialListCapacity), _instance(VK_NULL_HANDLE)
{
}

WindowListInternal::~WindowListInternal()
{
}

IDObject<WindowPointer> WindowListInternal::CreateWindow(WindowCreationData data, size_t addReserved)
{
	return _windowList.AddObject(std::make_unique<WindowInternal>(data), addReserved);
}

bool WindowListInternal::DeleteWindow(IDObject<WindowPointer> windowID, bool throwOnIDNotFound)
{
	return _windowList.RemoveObject(windowID, throwOnIDNotFound);
}

void WindowListInternal::DeleteAll(size_t capacityAfterReserve)
{
	_windowList.Reset(capacityAfterReserve);
}

WindowInternal& WindowListInternal::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	auto& window = _windowList.GetObject(windowID);

	return *window;
}

const WindowInternal& WindowListInternal::GetWindowSimplifier(IDObject<WindowPointer> windowID) const
{
	auto& window = _windowList.GetConstObject(windowID);

	return *window;
}
