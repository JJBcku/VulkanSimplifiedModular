export module VulkanSimplifiers.SharedDataList;

import VulkanSimplifiers.SharedDataList.Internal;

export class SharedDataListSimplifier
{
public:
	SharedDataListSimplifier(SharedDataListInternal& ref);
	~SharedDataListSimplifier();

	SharedDataListSimplifier& operator=(const SharedDataListSimplifier&) noexcept = delete;

private:
	SharedDataListInternal& _internal;
};