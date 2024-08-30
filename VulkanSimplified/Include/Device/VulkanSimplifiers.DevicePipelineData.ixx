export module VulkanSimplifiers.DevicePipelineData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.DevicePipelineData.Internal;
import VulkanSimplifiers.DevicePipelineData.LayoutCreationData;
import VulkanSimplifiers.DevicePipelineData.Data;

import VulkanSimplifiers.DevicePipelineData.GraphicPipelineCreationData;

export class DevicePipelineDataSimplifier
{
public:
	DevicePipelineDataSimplifier(DevicePipelineDataInternal& ref);
	~DevicePipelineDataSimplifier();

	DevicePipelineDataSimplifier& operator=(const DevicePipelineDataSimplifier&) noexcept = delete;

	IDObject<AutoCleanupPipelineLayout> AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserve = 0);
	std::vector<IDObject<AutoCleanupGraphicsPipeline>> AddGraphicPipelines(const std::vector<GraphicPipelineCreationData>& creationDataList, size_t addOnReserve = 0);

private:
	DevicePipelineDataInternal& _internal;
};