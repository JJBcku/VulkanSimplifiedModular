export module VulkanData.DeviceDependent;

import std;
import ListTemplates.IDObject;

export import VulkanSimplifiers.ShaderList.Data;

export struct VulkanDataDeviceDependent
{
	IDObject<AutoCleanUpFragmentShader> fragmentShader;
	IDObject<AutoCleanUpVertexShader> vertexShader;

	VulkanDataDeviceDependent() = default;
};