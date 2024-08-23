export module VulkanSimplifiers.LogicalDeviceMain.CreationData;

export import VulkanSimplifiers.ShaderList.CreationData;
export import VulkanSimplifiers.DeviceDescriptorData.CreationData;

export struct DeviceMainCreationData
{
	ShaderListCreationData shaderList;
	DeviceDesriptorDataCreationData deviceDescriptors;

	DeviceMainCreationData() = default;
};