export module VulkanSimplifiers.LogicalDeviceMain.CreationData;

export import VulkanSimplifiers.ShaderList.CreationData;
export import VulkanSimplifiers.DeviceDescriptorData.CreationData;
export import VulkanSimplifiers.DeviceRenderPassData.CreationData;
export import VulkanSimplifiers.DevicePipelineData.CreationData;
export import VulkanSimplifiers.ImageDataList.CreationData;
export import VulkanSimplifiers.MemoryObjectsList.CreationData;

export struct DeviceMainCreationData
{
	ShaderListCreationData shaderList;
	DeviceDescriptorDataCreationData deviceDescriptors;
	DeviceRenderPassCreationData renderPass;
	DevicePipelineDataCreationData devicePipelines;
	ImageDataCreationData imageList;
	MemoryListCreationData memoryList;

	DeviceMainCreationData() = default;
};