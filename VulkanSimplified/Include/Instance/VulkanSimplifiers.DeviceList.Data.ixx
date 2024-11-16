export module VulkanSimplifiers.DeviceList.Data;

import std;
import VulkanSimplifiers.LogicalDeviceMain.Internal;

export struct LogicalDevicePointer
{
	std::unique_ptr<LogicalDeviceMainInternal> pointer;

	LogicalDevicePointer() = default;
	LogicalDevicePointer(const LogicalDevicePointer&) noexcept = delete;
	LogicalDevicePointer(LogicalDevicePointer&& rhs) noexcept : pointer(std::move(rhs.pointer)) {};

	LogicalDevicePointer& operator= (const LogicalDevicePointer&) noexcept = delete;
	LogicalDevicePointer& operator= (LogicalDevicePointer&& rhs) noexcept
	{
		pointer = std::move(rhs.pointer);
		return *this;
	}

	LogicalDevicePointer(std::unique_ptr<LogicalDeviceMainInternal>&& moved) : pointer(std::move(moved)) {};
};