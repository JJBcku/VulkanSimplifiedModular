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