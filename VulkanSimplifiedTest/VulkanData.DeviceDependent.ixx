export module VulkanData.DeviceDependent;

import std;
import ListTemplates.IDObject;

export import VulkanSimplifiers.ShaderList.Data;
export import VulkanSimplifiers.Common.DataFormatFlags;

export struct VulkanDataDeviceDependent
{
	IDObject<AutoCleanUpFragmentShader> fragmentShader;
	IDObject<AutoCleanUpVertexShader> vertexShader;

	DataFormatSetIndependentID surfaceFormat;

	VulkanDataDeviceDependent() = default;
};