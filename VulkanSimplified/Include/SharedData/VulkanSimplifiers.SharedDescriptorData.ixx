export module VulkanSimplifiers.SharedDescriptorData;

import VulkanSimplifiers.SharedDescriptorData.Internal;

export class SharedDescriptorDataSimplifier
{
public:
	SharedDescriptorDataSimplifier(SharedDescriptorDataInternal& ref);
	~SharedDescriptorDataSimplifier();

	SharedDescriptorDataSimplifier& operator=(const SharedDescriptorDataSimplifier&) noexcept = delete;

private:
	SharedDescriptorDataInternal& _internal;
};