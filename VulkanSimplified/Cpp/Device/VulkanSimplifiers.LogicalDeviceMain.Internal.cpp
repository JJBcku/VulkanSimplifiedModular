module VulkanSimplifiers.LogicalDeviceMain.Internal;

LogicalDeviceMainInternal::LogicalDeviceMainInternal(const LogicalDeviceInitData& initData, const DeviceMainCreationData& mainCreationData, WindowListInternal& windowList, 
	const SharedDataListInternal& sharedDataList) : _core(initData, windowList), _shaderList(mainCreationData.shaderList, _core.GetDevice()),
	_descriptorList(mainCreationData.deviceDescriptors, _core.GetDevice(), sharedDataList.GetSharedDescriptorDataSimplifier()),
	_renderPassList(mainCreationData.renderPass, sharedDataList.GetSharedRenderPassDataSimplifier(), _core.GetDevice()),
	_pipelineDataList(mainCreationData.devicePipelines, sharedDataList.GetSharedPipelineDataSimplifier(), _descriptorList, _shaderList, _renderPassList, _core.GetDevice()),
	_imageList(mainCreationData.imageList, _core, _core.GetDevice())
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

ImageDataListInternal& LogicalDeviceMainInternal::GetImageDataListSimplifier()
{
	return _imageList;
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

const ImageDataListInternal& LogicalDeviceMainInternal::GetImageDataListSimplifier() const
{
	return _imageList;
}
