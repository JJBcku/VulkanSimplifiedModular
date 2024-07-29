export module VulkanSimplifiers.Common.VulkanVersionData;

import std;

export class VulkanVersionData
{
public:
	VulkanVersionData(std::uint16_t variant = 0, std::uint16_t major = 0, std::uint16_t minor = 0, std::uint16_t patch = 0);
	VulkanVersionData(std::uint32_t vulkanApiVersion);

	std::uint16_t GetVulkanVariantVersion() const;
	std::uint16_t GetVulkanMajorVersion() const;
	std::uint16_t GetVulkanMinorVersion() const;
	std::uint16_t GetVulkanPatchVersion() const;

	void SetVulkanVariantVersion(std::uint16_t variant);
	void SetVulkanMajorVersion(std::uint16_t major);
	void SetVulkanMinorVersion(std::uint16_t minor);
	void SetVulkanPatchVersion(std::uint16_t patch);

private:
	std::uint16_t _variant;
	std::uint16_t _major;
	std::uint16_t _minor;
	std::uint16_t _patch;
};