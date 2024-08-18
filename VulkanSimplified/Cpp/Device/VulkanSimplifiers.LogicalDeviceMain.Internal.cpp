module VulkanSimplifiers.LogicalDeviceMain.Internal;

LogicalDeviceMainInternal::LogicalDeviceMainInternal(const LogicalDeviceInitData& initData, const DeviceMainCreationData& mainCreationData, WindowListInternal& windowList) :
	_windowList(windowList), _core(initData, windowList), _shaderList(mainCreationData.shaderList, _core.GetDevice())
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

const LogicalDeviceCoreInternal& LogicalDeviceMainInternal::GetLogicalDeviceCoreSimplifier() const
{
	return _core;
}

const ShaderListInternal& LogicalDeviceMainInternal::GetShaderListSimplifier() const
{
	return _shaderList;
}
