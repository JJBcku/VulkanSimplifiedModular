module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.SynchronizationList.InternalData;

export class AutoCleanupFence
{
public:
	AutoCleanupFence(VkDevice device, VkFence fence);
	~AutoCleanupFence();

	VkFence GetFence() const;

	AutoCleanupFence(const AutoCleanupFence&) noexcept = delete;
	AutoCleanupFence(AutoCleanupFence&& rhs) noexcept;

	AutoCleanupFence& operator=(const AutoCleanupFence&) noexcept = delete;
	AutoCleanupFence& operator=(AutoCleanupFence&& rhs) noexcept;

private:
	VkDevice _device;
	VkFence _fence;

	void DestroyFence();
};

export class AutoCleanupSemaphore
{
public:
	AutoCleanupSemaphore(VkDevice device, VkSemaphore semaphore);
	~AutoCleanupSemaphore();

	AutoCleanupSemaphore(const AutoCleanupSemaphore&) noexcept = delete;
	AutoCleanupSemaphore(AutoCleanupSemaphore&& rhs) noexcept;

	AutoCleanupSemaphore& operator=(const AutoCleanupSemaphore&) noexcept = delete;
	AutoCleanupSemaphore& operator=(AutoCleanupSemaphore&& rhs) noexcept;

	VkSemaphore GetSemaphore() const;

private:
	VkDevice _device;
	VkSemaphore _semaphore;

	void DestroySemaphore();
};