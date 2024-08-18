module;

#include <vulkan/vulkan.hpp>

export module VulkanSimplifiers.ShaderList.InternalData;

export class AutoCleanUpShader
{
public:
	AutoCleanUpShader(VkDevice device, VkShaderModule shader);
	~AutoCleanUpShader();

	AutoCleanUpShader(const AutoCleanUpShader&) noexcept = delete;
	AutoCleanUpShader(AutoCleanUpShader&& rhs) noexcept;

	AutoCleanUpShader& operator=(const AutoCleanUpShader&) noexcept = delete;
	AutoCleanUpShader& operator=(AutoCleanUpShader&& rhs) noexcept;

private:
	VkDevice _device;
	VkShaderModule _shader;
};

export class AutoCleanUpFragmentShader : public AutoCleanUpShader
{
public:
	AutoCleanUpFragmentShader(VkDevice device, VkShaderModule shader);
	~AutoCleanUpFragmentShader();

	AutoCleanUpFragmentShader(const AutoCleanUpFragmentShader&) noexcept = delete;
	AutoCleanUpFragmentShader(AutoCleanUpFragmentShader&& rhs) noexcept;

	AutoCleanUpFragmentShader& operator=(const AutoCleanUpFragmentShader&) noexcept = delete;
	AutoCleanUpFragmentShader& operator=(AutoCleanUpFragmentShader&& rhs) noexcept;
};

export class AutoCleanUpVertexShader : public AutoCleanUpShader
{
public:
	AutoCleanUpVertexShader(VkDevice device, VkShaderModule shader);
	~AutoCleanUpVertexShader();

	AutoCleanUpVertexShader(const AutoCleanUpVertexShader&) noexcept = delete;
	AutoCleanUpVertexShader(AutoCleanUpVertexShader&& rhs) noexcept;

	AutoCleanUpVertexShader& operator=(const AutoCleanUpVertexShader&) noexcept = delete;
	AutoCleanUpVertexShader& operator=(AutoCleanUpVertexShader&& rhs) noexcept;
};