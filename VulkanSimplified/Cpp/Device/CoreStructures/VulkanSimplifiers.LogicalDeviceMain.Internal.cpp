module VulkanSimplifiers.LogicalDeviceMain.Internal;

LogicalDeviceMainInternal::LogicalDeviceMainInternal(const LogicalDeviceInitData& initData, const PhysicalDeviceInternal& physicalDevice,
	const DeviceMainCreationData& mainCreationData, WindowListInternal& windowList, const SharedDataListInternal& sharedDataList) : _core(initData, windowList),
	_shaderList(mainCreationData.shaderList, _core.GetDevice()),
	_descriptorList(mainCreationData.deviceDescriptors, _core.GetDevice(), sharedDataList.GetSharedDescriptorDataSimplifier()),
	_renderPassList(mainCreationData.renderPass, sharedDataList.GetSharedRenderPassDataSimplifier(), _core.GetDevice()),
	_pipelineDataList(mainCreationData.devicePipelines, sharedDataList.GetSharedPipelineDataSimplifier(), _descriptorList, _shaderList, _renderPassList, _core.GetDevice()),
	_memoryList(_core.GetDevice(), physicalDevice.GetDeviceMemoryData(), mainCreationData.memoryList),
	_imageList(mainCreationData.imageList, _core, _renderPassList, _memoryList, _core.GetDevice()), _synchronizationList(_core.GetDevice(), mainCreationData.synchronizationList),
	_commandPoolList(_core, _renderPassList, sharedDataList.GetSharedRenderPassDataSimplifier(), _pipelineDataList, _synchronizationList, _imageList, windowList,
		mainCreationData.commandPoolList)
{
}

LogicalDeviceMainInternal::~LogicalDeviceMainInternal()
{
}

LogicalDeviceCoreInternal& LogicalDeviceMainInternal::GetLogicalDeviceCoreSimplifier()
{
	return _core;
}

ShaderListInternal& LogicalDeviceMainInternal::GetShaderListSimplifier()
{
	return _shaderList;
}

DeviceDescriptorDataInternal& LogicalDeviceMainInternal::GetDeviceDescriptorDataSimplifier()
{
	return _descriptorList;
}

DeviceRenderPassDataInternal& LogicalDeviceMainInternal::GetRenderPassListSimplifier()
{
	return _renderPassList;
}

DevicePipelineDataInternal& LogicalDeviceMainInternal::GetDevicePipelineDataSimplifier()
{
	return _pipelineDataList;
}

MemoryObjectsListInternal& LogicalDeviceMainInternal::GetMemoryObjectsListSimplifier()
{
	return _memoryList;
}

ImageDataListInternal& LogicalDeviceMainInternal::GetImageDataListSimplifier()
{
	return _imageList;
}

SynchronizationListInternal& LogicalDeviceMainInternal::GetSynchronizationListSimplifier()
{
	return _synchronizationList;
}

CommandPoolListInternal& LogicalDeviceMainInternal::GetCommandPoolListSimplifier()
{
	return _commandPoolList;
}

const LogicalDeviceCoreInternal& LogicalDeviceMainInternal::GetLogicalDeviceCoreSimplifier() const
{
	return _core;
}

const ShaderListInternal& LogicalDeviceMainInternal::GetShaderListSimplifier() const
{
	return _shaderList;
}

const DeviceDescriptorDataInternal& LogicalDeviceMainInternal::GetDeviceDescriptorDataSimplifier() const
{
	return _descriptorList;
}

const DeviceRenderPassDataInternal& LogicalDeviceMainInternal::GetRenderPassListSimplifier() const
{
	return _renderPassList;
}

const DevicePipelineDataInternal& LogicalDeviceMainInternal::GetDevicePipelineDataSimplifier() const
{
	return _pipelineDataList;
}

const MemoryObjectsListInternal& LogicalDeviceMainInternal::GetMemoryObjectsListSimplifier() const
{
	return _memoryList;
}

const ImageDataListInternal& LogicalDeviceMainInternal::GetImageDataListSimplifier() const
{
	return _imageList;
}

const SynchronizationListInternal& LogicalDeviceMainInternal::GetSynchronizationListSimplifier() const
{
	return _synchronizationList;
}

const CommandPoolListInternal& LogicalDeviceMainInternal::GetCommandPoolListSimplifier() const
{
	return _commandPoolList;
}
