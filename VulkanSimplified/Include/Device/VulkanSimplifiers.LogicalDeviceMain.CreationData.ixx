export module VulkanSimplifiers.LogicalDeviceMain.CreationData;

export import VulkanSimplifiers.ShaderList.CreationData;
export import VulkanSimplifiers.DeviceDescriptorData.CreationData;
export import VulkanSimplifiers.DevicePipelineData.CreationData;

export struct DeviceMainCreationData
{
	ShaderListCreationData shaderList;
	DeviceDescriptorDataCreationData deviceDescriptors;
	DevicePipelineDataCreationData devicePipelines;

	DeviceMainCreationData() = default;
};