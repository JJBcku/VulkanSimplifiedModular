export module VulkanSimplifiers.SharedPipelineData.Internal;

import std;
import ListTemplates.UnsortedList;

import VulkanSimplifiers.SharedPipelineData.InternalData;
import VulkanSimplifiers.SharedPipelineData.CreationData;

export class SharedPipelineDataInternal
{
public:
	SharedPipelineDataInternal(SharedPipelineDataCreationInfo initInfo);
	~SharedPipelineDataInternal();

	IDObject<ShaderSpecializationElement> AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve);
	IDObject<ShaderSharedPipelineData> AddShaderSharedPipelineData(const std::string& entryPointName,
		const std::vector<IDObject<ShaderSpecializationElement>>& specializations, size_t addOnReserve);

private:
	UnsortedList<ShaderSpecializationElement> _shaderSpecializationElements;
	UnsortedList<ShaderSharedPipelineData> _shaderPipelineInfo;
};