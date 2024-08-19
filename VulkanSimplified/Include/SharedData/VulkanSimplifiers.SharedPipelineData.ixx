export module VulkanSimplifiers.SharedPipelineData;

import std;
import ListTemplates.IDObject;

import VulkanSimplifiers.SharedPipelineData.Internal;
import VulkanSimplifiers.SharedPipelineData.Data;

export class SharedPipelineDataSimplifier
{
public:
	SharedPipelineDataSimplifier(SharedPipelineDataInternal& ref);
	~SharedPipelineDataSimplifier();

	SharedPipelineDataSimplifier& operator=(const SharedPipelineDataSimplifier&) noexcept = delete;

	IDObject<ShaderSpecializationElement> AddShaderSpecializationElement(std::uint32_t constantID, std::uint32_t dataOffset, size_t dataSize, size_t addOnReserve = 0);
	IDObject<ShaderSharedPipelineData> AddShaderSharedPipelineData(const std::string& entryPointName,
		const std::vector<IDObject<ShaderSpecializationElement>>& specializations, size_t addOnReserve = 0);

private:
	SharedPipelineDataInternal& _internal;
};