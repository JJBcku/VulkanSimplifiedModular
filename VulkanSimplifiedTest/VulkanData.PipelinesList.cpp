module VulkanData.PipelinesList;

bool VulkanPipelineData::operator==(const IDObject<PipelineViewportData>& rhsPipelineViewport) const
{
	return pipelineViewport == rhsPipelineViewport;
}
