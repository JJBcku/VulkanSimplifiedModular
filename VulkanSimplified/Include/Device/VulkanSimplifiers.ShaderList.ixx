export module VulkanSimplifiers.ShaderList;

import VulkanSimplifiers.ShaderList.Internal;

export class ShaderListSimplifier
{
public:
	ShaderListSimplifier(ShaderListInternal& ref);
	~ShaderListSimplifier();

	ShaderListSimplifier& operator=(const ShaderListSimplifier&) noexcept = delete;

private:
	ShaderListInternal& _internal;
};