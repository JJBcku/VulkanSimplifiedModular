module VulkanSimplifiers.Common.VulkanVersionData;

VulkanVersionData::VulkanVersionData(std::uint16_t variant, std::uint16_t major, std::uint16_t minor, std::uint16_t patch)
{
	if (variant > 7)
		throw std::runtime_error("VulkanVersionData Error: Program was given too big value for variant version!");

	if (major > 0x7F)
		throw std::runtime_error("VulkanVersionData Error: Program was given too big value for major version!");

	if (minor > 0x3FF)
		throw std::runtime_error("VulkanVersionData Error: Program was given too big value for minor version!");

	if (patch > 0xFFF)
		throw std::runtime_error("VulkanVersionData Error: Program was given too big value for patch version!");

	_variant = variant;
	_major = major;
	_minor = minor;
	_patch = patch;
}

VulkanVersionData::VulkanVersionData(std::uint32_t vulkanApiVersion)
{
	_variant = vulkanApiVersion >> 29;
	_major = (vulkanApiVersion >> 22) & 0x7F;
	_minor = (vulkanApiVersion >> 12) & 0x3FF;
	_patch = vulkanApiVersion & 0xFFF;
}

std::uint16_t VulkanVersionData::GetVulkanVariantVersion() const
{
	return _variant;
}

std::uint16_t VulkanVersionData::GetVulkanMajorVersion() const
{
	return _major;
}

std::uint16_t VulkanVersionData::GetVulkanMinorVersion() const
{
	return _minor;
}

std::uint16_t VulkanVersionData::GetVulkanPatchVersion() const
{
	return _patch;
}

void VulkanVersionData::SetVulkanVariantVersion(std::uint16_t variant)
{
	if (variant > 7)
		throw std::runtime_error("VulkanVersionData SetVulkanVariantVersion Error: Program was given too big value for variant version!");

	_variant = variant;
}

void VulkanVersionData::SetVulkanMajorVersion(std::uint16_t major)
{
	if (major > 0x7F)
		throw std::runtime_error("VulkanVersionData SetVulkanMajorVersion Error: Program was given too big value for major version!");

	_major = major;
}

void VulkanVersionData::SetVulkanMinorVersion(std::uint16_t minor)
{
	if (minor > 0x3FF)
		throw std::runtime_error("VulkanVersionData SetVulkanMinorVersion Error: Program was given too big value for minor version!");

	_minor = minor;
}

void VulkanVersionData::SetVulkanPatchVersion(std::uint16_t patch)
{
	if (patch > 0xFFF)
		throw std::runtime_error("VulkanVersionData SetVulkanPatchVersion Error: Program was given too big value for patch version!");

	_patch = patch;
}
