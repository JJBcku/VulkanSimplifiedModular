export module VulkanSimplifiers.Window;

import std;

import VulkanSimplifiers.Window.Internal;

export class WindowSimplifier
{
public:
	WindowSimplifier(WindowInternal& ref);
	~WindowSimplifier();

	WindowSimplifier& operator=(WindowSimplifier&) const = delete;

	bool GetQuit() const;
	bool GetPaused() const;
	bool GetResized();

	std::uint32_t GetWidth() const;
	std::uint32_t GetHeight() const;

private:
	WindowInternal& _internal;
};