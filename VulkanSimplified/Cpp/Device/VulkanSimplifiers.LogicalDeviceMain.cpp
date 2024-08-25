module VulkanSimplifiers.LogicalDeviceMain;

LogicalDeviceMainSimplifier::LogicalDeviceMainSimplifier(LogicalDeviceMainInternal& ref) : _internal(ref)
{
}

LogicalDeviceMainSimplifier::~LogicalDeviceMainSimplifier()
{
}

LogicalDeviceCoreSimplifier LogicalDeviceMainSimplifier::GetLogicalDeviceCoreSimplifier()
{
	return _internal.GetLogicalDeviceCoreSimplifier();
}

ShaderListSimplifier LogicalDeviceMainSimplifier::GetShaderListSimplifier()
{
	return _internal.GetShaderListSimplifier();
}

DeviceDescriptorDataSimpifier LogicalDeviceMainSimplifier::GetDeviceDescriptorDataSimplifier()
{
	return _internal.GetDeviceDescriptorDataSimplifier();
}

DevicePipelineDataSimplifier LogicalDeviceMainSimplifier::GetDevicePipelineDataSimplifier()
{
	return _internal.GetDevicePipelineDataSimplifier();
}

const LogicalDeviceCoreSimplifier LogicalDeviceMainSimplifier::GetLogicalDeviceCoreSimplifier() const
{
	return _internal.GetLogicalDeviceCoreSimplifier();
}

const ShaderListSimplifier LogicalDeviceMainSimplifier::GetShaderListSimplifier() const
{
	return _internal.GetShaderListSimplifier();
}

const DeviceDescriptorDataSimpifier LogicalDeviceMainSimplifier::GetDeviceDescriptorDataSimplifier() const
{
	return _internal.GetDeviceDescriptorDataSimplifier();
}

const DevicePipelineDataSimplifier LogicalDeviceMainSimplifier::GetDevicePipelineDataSimplifier() const
{
	return _internal.GetDevicePipelineDataSimplifier();
}