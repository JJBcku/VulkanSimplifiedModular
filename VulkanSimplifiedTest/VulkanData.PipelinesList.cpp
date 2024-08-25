module VulkanData.PipelinesList;

bool VulkanPipelineData::operator==(const IDObject<PipelineViewportData>& pipelineViewport)
{
	return _pipelineViewport == pipelineViewport;
}
