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

DeviceRenderPassDataSimplifier LogicalDeviceMainSimplifier::GetRenderPassListSimplifier()
{
	return _internal.GetRenderPassListSimplifier();
}

DevicePipelineDataSimplifier LogicalDeviceMainSimplifier::GetDevicePipelineDataSimplifier()
{
	return _internal.GetDevicePipelineDataSimplifier();
}

ImageDataListSimplifier LogicalDeviceMainSimplifier::GetImageDataListSimplifier()
{
	return _internal.GetImageDataListSimplifier();
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

const DeviceRenderPassDataSimplifier LogicalDeviceMainSimplifier::GetRenderPassListSimplifier() const
{
	return _internal.GetRenderPassListSimplifier();
}

const DevicePipelineDataSimplifier LogicalDeviceMainSimplifier::GetDevicePipelineDataSimplifier() const
{
	return _internal.GetDevicePipelineDataSimplifier();
}

const ImageDataListSimplifier LogicalDeviceMainSimplifier::GetImageDataListSimplifier() const
{
	return _internal.GetImageDataListSimplifier();
}
