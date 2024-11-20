export module VulkanData.DeviceDependent;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.ShaderList.Data;
export import VulkanSimplifiers.Common.DataFormatFlags;
export import VulkanSimplifiers.CommandPool.Data;
export import VulkanSimplifiers.NIRCommandPool.Data;

export struct VulkanDataDeviceDependent
{
	IDObject<AutoCleanUpFragmentShader> fragmentShader;
	IDObject<AutoCleanUpVertexShader> vertexShader;

	DataFormatSetIndependentID surfaceFormat;

	IDObject<NIRCommandPoolInternal> graphicsCommandPool;
	std::vector<IDObject<PrimaryNIRCommandBufferInternal>> graphicsCommandBuffers;

	std::optional<IDObject<NIRCommandPoolInternal>> transferCommandPool;
	std::vector<IDObject<PrimaryNIRCommandBufferInternal>> transferCommandBuffers;

	std::optional<IDObject<NIRCommandPoolInternal>> presentCommandPool;
	std::vector<IDObject<PrimaryNIRCommandBufferInternal>> presentCommandBuffers;

	VulkanDataDeviceDependent() = default;
};