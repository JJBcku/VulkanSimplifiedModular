export module VulkanSimplifiers.SharedPipelineData.Internal;

import ListTemplates.UnsortedList;
import VulkanSimplifiers.SharedPipelineData.InternalData;
import VulkanSimplifiers.SharedPipelineData.CreationData;

export class SharedPipelineDataInternal
{
public:
	SharedPipelineDataInternal(SharedPipelineDataCreationInfo initInfo);
	~SharedPipelineDataInternal();

private:
	UnsortedList<ShaderSpecializationElement> _shaderSpecializationElements;
};