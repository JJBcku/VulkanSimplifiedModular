export module VulkanData.DeviceDependent;

import std;
export import ListTemplates.IDObject;

export import VulkanSimplifiers.ShaderList.Data;
export import VulkanSimplifiers.Common.DataFormatFlags;
export import VulkanSimplifiers.CommandPool.Data;

export struct VulkanDataDeviceDependent
{
	IDObject<AutoCleanUpFragmentShader> fragmentShader;
	IDObject<AutoCleanUpVertexShader> vertexShader;

	DataFormatSetIndependentID surfaceFormat;

	IDObject<NIRCommandPoolInternal> graphicsCommandPool;
	std::optional<IDObject<NIRCommandPoolInternal>> transferCommandPool;
	std::optional<IDObject<NIRCommandPoolInternal>> presentCommandPool;

	VulkanDataDeviceDependent() = default;
};