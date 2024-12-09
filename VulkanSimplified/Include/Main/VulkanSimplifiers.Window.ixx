export module VulkanSimplifiers.Window;

import std;

import VulkanSimplifiers.Window.Internal;

export class WindowSimplifier
{
public:
	WindowSimplifier(WindowInternal& ref);
	~WindowSimplifier();

	WindowSimplifier& operator=(WindowSimplifier&) const = delete;

	bool IsClosingRequested() const;
	bool IsPaused() const;
	bool IsResized();

	std::uint32_t GetWidth() const;
	std::uint32_t GetHeight() const;

private:
	WindowInternal& _internal;
};