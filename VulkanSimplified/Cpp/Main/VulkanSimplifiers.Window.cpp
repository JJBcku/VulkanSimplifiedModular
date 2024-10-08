module VulkanSimplifiers.Window;

WindowSimplifier::WindowSimplifier(WindowInternal& ref) : _internal(ref)
{
}

WindowSimplifier::~WindowSimplifier()
{
}

bool WindowSimplifier::GetQuit() const
{
	return _internal.GetQuit();
}

bool WindowSimplifier::GetPaused() const
{
	return _internal.GetPaused();
}

bool WindowSimplifier::GetResized()
{
	return _internal.GetResized();
}

std::uint32_t WindowSimplifier::GetWidth() const
{
	return _internal.GetWidth();
}

std::uint32_t WindowSimplifier::GetHeight() const
{
	return _internal.GetHeight();
}
