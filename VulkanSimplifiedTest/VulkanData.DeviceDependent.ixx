export module VulkanData.DeviceDependent;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.ShaderList.Data;
export import VulkanSimplifiers.Common.DataFormatFlags;
export import VulkanSimplifiers.CommandPool.Data;
export import VulkanSimplifiers.IRCommandPool.Data;
export import VulkanSimplifiers.SynchronizationList.Data;

export struct VulkanDataDeviceDependent
{
	IDObject<AutoCleanUpFragmentShader> fragmentShader;
	IDObject<AutoCleanUpVertexShader> vertexShader;

	DataFormatSetIndependentID surfaceFormat;

	size_t imageAmount;

	IDObject<std::unique_ptr<IRCommandPoolInternal>> graphicsCommandPool;
	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> graphicsCommandBuffers;

	std::optional<IDObject<std::unique_ptr<IRCommandPoolInternal>>> transferCommandPool;
	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> transferCommandBuffers;

	std::optional<IDObject<std::unique_ptr<IRCommandPoolInternal>>> presentCommandPool;
	std::vector<IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>> presentCommandBuffers;

	std::vector<IDObject<AutoCleanupFence>> inFlightFences;
	std::vector<IDObject<AutoCleanupSemaphore>> imageAvailableSemaphores;
	std::vector<IDObject<AutoCleanupSemaphore>> renderingFinishedSemaphores;
	std::vector<IDObject<AutoCleanupSemaphore>> queueTransferFinishedSemaphores;

	VulkanDataDeviceDependent() = default;
};