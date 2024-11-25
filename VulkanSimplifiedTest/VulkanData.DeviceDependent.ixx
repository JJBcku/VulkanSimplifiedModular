export module VulkanData.DeviceDependent;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.ShaderList.Data;
export import VulkanSimplifiers.Common.DataFormatFlags;
export import VulkanSimplifiers.CommandPool.Data;
export import VulkanSimplifiers.NIRCommandPool.Data;
export import VulkanSimplifiers.SynchronizationList.Data;

export struct VulkanDataDeviceDependent
{
	IDObject<AutoCleanUpFragmentShader> fragmentShader;
	IDObject<AutoCleanUpVertexShader> vertexShader;

	DataFormatSetIndependentID surfaceFormat;

	size_t imageAmount;

	IDObject<std::unique_ptr<NIRCommandPoolInternal>> graphicsCommandPool;
	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> graphicsCommandBuffers;

	std::optional<IDObject<std::unique_ptr<NIRCommandPoolInternal>>> transferCommandPool;
	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> transferCommandBuffers;

	std::optional<IDObject<std::unique_ptr<NIRCommandPoolInternal>>> presentCommandPool;
	std::vector<IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>> presentCommandBuffers;

	std::vector<IDObject<AutoCleanupFence>> inFlightFences;
	std::vector<IDObject<AutoCleanupSemaphore>> imageAvailableSemaphores;
	std::vector<IDObject<AutoCleanupSemaphore>> renderingFinishedSemaphores;

	VulkanDataDeviceDependent() = default;
};