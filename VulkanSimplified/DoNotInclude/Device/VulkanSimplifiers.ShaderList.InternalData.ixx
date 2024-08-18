module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.ShaderList.InternalData;

export class AutoCleanUpShader
{
public:
	AutoCleanUpShader(VkDevice device, VkShaderModule shader);
	~AutoCleanUpShader();

private:
	VkDevice _device;
	VkShaderModule _shader;
};

export class AutoCleanUpFragmentShader : public AutoCleanUpShader
{
public:
	AutoCleanUpFragmentShader(VkDevice device, VkShaderModule shader);
	~AutoCleanUpFragmentShader();
};

export class AutoCleanUpVertexShader : public AutoCleanUpShader
{
public:
	AutoCleanUpVertexShader(VkDevice device, VkShaderModule shader);
	~AutoCleanUpVertexShader();
};