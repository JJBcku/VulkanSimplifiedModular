module VulkanSimplifiers.WindowList;

WindowListSimplifier::WindowListSimplifier(WindowListInternal& ref) : _internal(ref)
{
}

WindowListSimplifier::~WindowListSimplifier()
{
}

IDObject<WindowPointer> WindowListSimplifier::CreateWindow(WindowCreationData data, size_t addOnReservation)
{
	return _internal.CreateWindow(data, addOnReservation);
}

bool WindowListSimplifier::DeleteWindow(IDObject<WindowPointer> windowID, bool throwOnIDNotFound)
{
	return _internal.DeleteWindow(windowID, throwOnIDNotFound);
}

void WindowListSimplifier::DeleteAll(size_t capacityAfterReserve)
{
	_internal.DeleteAll(capacityAfterReserve);
}

WindowSimplifier WindowListSimplifier::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	return _internal.GetWindowSimplifier(windowID);
}

const WindowSimplifier WindowListSimplifier::GetWindowSimplifier(IDObject<WindowPointer> windowID) const
{
	return _internal.GetWindowSimplifier(windowID);
}
