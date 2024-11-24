export module VulkanSimplifiers.ImageDataList.Data;

import std;
export import ListTemplates.IDObject;

export class AutoCleanupImageView;
export class AutoCleanup2DSimpleImage;
export class AutoCleanupMipMapped2DImage;

export enum class ImageIDType : std::uint64_t
{
	UNKNOWN = 0,
	SIMPLE_2D = 1,
	MIPMAPPED_2D = 2,
};

export union ImageIDUnion
{
	ImageIDType type;

	struct
	{
		ImageIDType type;
		IDObject<AutoCleanup2DSimpleImage> ID;
	} simple2D;

	struct
	{
		ImageIDType type;
		IDObject<AutoCleanupMipMapped2DImage> ID;
	} mipMapped2D;

	ImageIDUnion();
};