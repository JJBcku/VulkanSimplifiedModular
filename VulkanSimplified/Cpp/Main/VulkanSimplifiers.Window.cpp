module VulkanSimplifiers.Window;

WindowSimplifier::WindowSimplifier(WindowInternal& ref) : _internal(ref)
{
}

WindowSimplifier::~WindowSimplifier()
{
}

bool WindowSimplifier::IsClosingRequested() const
{
	return _internal.IsClosingRequested();
}

bool WindowSimplifier::IsPaused() const
{
	return _internal.IsPaused();
}

bool WindowSimplifier::IsResized()
{
	return _internal.IsResized();
}

std::uint32_t WindowSimplifier::GetWidth() const
{
	return _internal.GetWidth();
}

std::uint32_t WindowSimplifier::GetHeight() const
{
	return _internal.GetHeight();
}
