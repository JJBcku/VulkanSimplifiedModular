module VulkanSimplifiers.LogicalDeviceMain.Internal;

LogicalDeviceMainInternal::LogicalDeviceMainInternal(const LogicalDeviceInitData& initData, const DeviceMainCreationData& mainCreationData, WindowListInternal& windowList, 
	const SharedDataListInternal& sharedDataList) : _core(initData, windowList), _shaderList(mainCreationData.shaderList, _core.GetDevice()),
	_descriptorList(mainCreationData.deviceDescriptors, _core.GetDevice(), sharedDataList.GetSharedDescriptorDataSimplifier())
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
