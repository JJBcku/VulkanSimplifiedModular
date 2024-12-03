module;

#include <vulkan/vulkan.hpp>

module VulkanSimplifiers.CommandPoolList.Internal;

CommandPoolListInternal::CommandPoolListInternal(const LogicalDeviceCoreInternal& deviceCore, const DeviceRenderPassDataInternal& deviceRenderPassData,
	const SharedRenderPassDataInternal& sharedRenderPassData, const DevicePipelineDataInternal& devicePipelineData, const SynchronizationListInternal& synchronizationList,
	const ImageDataListInternal& imageList, WindowListInternal& windowList, const CommandPoolListCreationData& creationData) : _deviceCore(deviceCore),
	_deviceRenderPassData(deviceRenderPassData), _sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList),
	_imageList(imageList), _windowList(windowList), _device(deviceCore.GetDevice())
{
	size_t queueFamiliesCount = _deviceCore.GetQueueFamiliesCount();

	if (queueFamiliesCount != creationData.queueGroupCreationData.size())
		throw std::runtime_error("CommandPoolListInternal::CommandPoolListInternal Error: queue families count to queue families creation data count mismatch!");

	if (queueFamiliesCount == 0)
		throw std::runtime_error("CommandPoolListInternal::CommandPoolListInternal Error: Program found no queue families!");

	_queueFamilies.emplace_front(deviceCore, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList,
		creationData.queueGroupCreationData[0], static_cast<std::uint32_t>(0));

	auto it = _queueFamilies.begin();

	for (size_t i = 1; i < queueFamiliesCount; ++i)
	{
		_queueFamilies.emplace_after(it, deviceCore, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList,
			creationData.queueGroupCreationData[i], static_cast<std::uint32_t>(i));

		it = _queueFamilies.begin();
		std::advance(it, i);
	}
}

CommandPoolListInternal::~CommandPoolListInternal()
{
}

CommandPoolQFGroupListInternal& CommandPoolListInternal::GetCommandPoolQFGroupListSimplifier(size_t queuesID)
{
	if (_queueFamilies.empty())
		throw std::runtime_error("CommandPoolListInternal::GetCommandPoolQFGroupListSimplifier Error: list is empty!");

	size_t queueFamily = _deviceCore.GetQueueFamily(queuesID);

	auto it = _queueFamilies.begin();

	std::ranges::advance(it, static_cast<std::ptrdiff_t>(queueFamily), _queueFamilies.cend());

	if (it == _queueFamilies.end())
		throw std::runtime_error("CommandPoolListInternal::GetCommandPoolQFGroupListSimplifier Error: Program tried to read beyond the list!");

	return *it;
}

const CommandPoolQFGroupListInternal& CommandPoolListInternal::GetCommandPoolQFGroupListSimplifier(size_t queuesID) const
{
	if (_queueFamilies.empty())
		throw std::runtime_error("CommandPoolListInternal::GetCommandPoolQFGroupListSimplifier Const Error: list is empty!");

	size_t queueFamily = _deviceCore.GetQueueFamily(queuesID);

	auto it = _queueFamilies.cbegin();

	std::ranges::advance(it, static_cast<std::ptrdiff_t>(queueFamily), _queueFamilies.cend());

	if (it == _queueFamilies.cend())
		throw std::runtime_error("CommandPoolListInternal::GetCommandPoolQFGroupListSimplifier Const Error: Program tried to read beyond the list!");

	return *it;
}