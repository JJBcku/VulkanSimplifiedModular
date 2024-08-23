export module VulkanSimplifiers.SharedDescriptorData.Internal;

import VulkanSimplifiers.SharedDescriptorData.CreationData;

export class SharedDescriptorDataInternal
{
public:
	SharedDescriptorDataInternal(const SharedDescriptorDataCreationInfo& creationInfo);
	~SharedDescriptorDataInternal();

private:
	long long int stump;
};