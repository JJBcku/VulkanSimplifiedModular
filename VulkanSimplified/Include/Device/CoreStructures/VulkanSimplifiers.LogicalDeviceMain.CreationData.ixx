export module VulkanSimplifiers.LogicalDeviceMain.CreationData;

export import VulkanSimplifiers.ShaderList.CreationData;
export import VulkanSimplifiers.DeviceDescriptorData.CreationData;
export import VulkanSimplifiers.DeviceRenderPassData.CreationData;
export import VulkanSimplifiers.DevicePipelineData.CreationData;
export import VulkanSimplifiers.ImageDataList.CreationData;
export import VulkanSimplifiers.MemoryObjectsList.CreationData;
export import VulkanSimplifiers.SynchronizationList.CreationData;
export import VulkanSimplifiers.CommandPoolList.CreationData;

export struct DeviceMainCreationData
{
	ShaderListCreationData shaderList;
	DeviceDescriptorDataCreationData deviceDescriptors;
	DeviceRenderPassCreationData renderPass;
	DevicePipelineDataCreationData devicePipelines;

	MemoryListCreationData memoryList;
	ImageDataCreationData imageList;

	SynchronizationListCreationData synchronizationList;

	CommandPoolListCreationData commandPoolList;

	DeviceMainCreationData() = default;
};