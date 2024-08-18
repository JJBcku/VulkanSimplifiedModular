export module VulkanSimplifiers.SharedDataList.Internal;

import VulkanSimplifiers.SharedDataList.CreationData;

export class SharedDataListInternal
{
public:
	SharedDataListInternal(SharedDataListCreationData creationData);
	~SharedDataListInternal();

private:
	long long int _stump;
};
