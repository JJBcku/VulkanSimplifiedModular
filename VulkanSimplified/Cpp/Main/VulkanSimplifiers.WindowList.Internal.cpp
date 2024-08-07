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
	return _windowList.AddObject(std::make_unique<WindowInternal>(data, _instance), addReserved);
}

bool WindowListInternal::DeleteWindow(IDObject<WindowPointer> windowID, bool throwOnIDNotFound)
{
	return _windowList.RemoveObject(windowID, throwOnIDNotFound);
}

void WindowListInternal::DeleteAll(size_t capacityAfterReserve)
{
	_windowList.Reset(capacityAfterReserve);
}

void WindowListInternal::SetInstance(VkInstance instance)
{
	if (_instance != VK_NULL_HANDLE)
		throw std::runtime_error("WindowListInternal::SetInstance Error: Program tried to set already set vulkan instance value!");

	_instance = instance;

	if (_instance != VK_NULL_HANDLE)
	{
		size_t listSize = _windowList.GetSize();

		for (size_t i = 0; i < listSize; i++)
		{
			auto& windowOptional = _windowList.GetObjectOptional(i);

			if (windowOptional.has_value())
			{
				auto& window = windowOptional.value();

				window->SetInstace(_instance);
			}
		}
	}
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
