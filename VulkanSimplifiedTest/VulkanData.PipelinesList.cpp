module VulkanData.PipelinesList;

bool VulkanPipelineData::operator==(const IDObject<PipelineViewportData>& rhsPipelineViewport)
{
	return pipelineViewport == rhsPipelineViewport;
}
