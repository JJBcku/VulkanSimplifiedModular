module RunProgram.CreateRenderPassData;

void CreateRenderPassData(VulkanData& data)
{
	data.renderPassData = std::make_unique<VulkanRenderPassData>();

	DataFormatSetIndependentID format;

	auto& srgb = data.instanceDependent->surfaceSupport.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace;
	auto& blitDst = data.instanceDependent->deviceFormatsSupport.formatFeaturesOptimalImageSupport.blitDst;

	if ((srgb.thirdSet & DATA_FORMAT_BGRA8_UNORM) == DATA_FORMAT_BGRA8_UNORM && (blitDst.thirdSet & DATA_FORMAT_BGRA8_UNORM) == DATA_FORMAT_BGRA8_UNORM)
	{
		format.dataSet = DataFormatSetEnum::DATA_SET_THREE;
		format.dataFormat = DATA_FORMAT_BGRA8_UNORM;
	}
	else
	{
		format.dataSet = DataFormatSetEnum::DATA_SET_SEVEN;
		format.dataFormat = DATA_FORMAT_RGBA8_UNORM;
	}

	auto sharedDataList = data.basicData->main->GetSharedDataListSimplifier();
	auto renderPassSharedDataList = sharedDataList.GetSharedRenderPassDataSimplifier();

	auto& renderPassData = *data.renderPassData;

	renderPassData.renderPassAttachments.push_back(renderPassSharedDataList.AddRenderPassAttachment(format, SAMPLE_1, RenderPassAttachmentLoadOP::CLEAR,
		RenderPassAttachmentStoreOP::STORE, ImageLayoutFlags::UNDEFINED, ImageLayoutFlags::PRESENT));

	renderPassData.colorAttachmentReference = renderPassSharedDataList.AddRenderPassAttachmentReference(0, ImageLayoutFlags::COLOR_ATTACHMENT);

	renderPassData.subpassDependency = renderPassSharedDataList.AddSubpassDependency(externalSubpass, 0, PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT,
		PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT, 0, AccessFlagBits::ACCESS_COLOR_WRITE);
}