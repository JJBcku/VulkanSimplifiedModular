module;

#include <vulkan\vulkan.hpp>

module VulkanSimplifiers.Common.DataFormatFlags;

DataFormatFullSet::DataFormatFullSet()
{
	firstSet = 0;
	secondSet = 0;
	thirdSet = 0;
	fourthSet = 0;
	fifthSet = 0;
	sixthSet = 0;
	seventhSet = 0;
}

DataFormatSetIndependentID::DataFormatSetIndependentID()
{
	dataSet = DataFormatSetEnum::DATA_SET_UNKNOWN;
	dataFormat = 0;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatSetEnum set, DataFormatFlags format)
{
	dataSet = set;
	dataFormat = format;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatFirstFlagSetBits format)
{
	dataSet = DataFormatSetEnum::DATA_SET_ONE;
	dataFormat = format;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatSecondFlagSetBits format)
{
	dataSet = DataFormatSetEnum::DATA_SET_TWO;
	dataFormat = format;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatThirdFlagSetBits format)
{
	dataSet = DataFormatSetEnum::DATA_SET_THREE;
	dataFormat = format;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatFourthFlagSetBits format)
{
	dataSet = DataFormatSetEnum::DATA_SET_FOUR;
	dataFormat = format;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatFifthFlagSetBits format)
{
	dataSet = DataFormatSetEnum::DATA_SET_FIVE;
	dataFormat = format;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatSixthFlagSetBits format)
{
	dataSet = DataFormatSetEnum::DATA_SET_SIX;
	dataFormat = format;
}

DataFormatSetIndependentID::DataFormatSetIndependentID(DataFormatSeventhFlagSetBits format)
{
	dataSet = DataFormatSetEnum::DATA_SET_SEVEN;
	dataFormat = format;
}

bool CheckFormatSupport(const DataFormatFullSet& checkedSet, const DataFormatSetIndependentID& formatID)
{
	switch (formatID.dataSet)
	{
	case DataFormatSetEnum::DATA_SET_ONE:
		return (checkedSet.firstSet & formatID.dataFormat) == formatID.dataFormat;
		break;
	case DataFormatSetEnum::DATA_SET_TWO:
		return (checkedSet.secondSet & formatID.dataFormat) == formatID.dataFormat;
		break;
	case DataFormatSetEnum::DATA_SET_THREE:
		return (checkedSet.thirdSet & formatID.dataFormat) == formatID.dataFormat;
		break;
	case DataFormatSetEnum::DATA_SET_FOUR:
		return (checkedSet.fourthSet & formatID.dataFormat) == formatID.dataFormat;
		break;
	case DataFormatSetEnum::DATA_SET_FIVE:
		return (checkedSet.fifthSet & formatID.dataFormat) == formatID.dataFormat;
		break;
	case DataFormatSetEnum::DATA_SET_SIX:
		return (checkedSet.sixthSet & formatID.dataFormat) == formatID.dataFormat;
		break;
	case DataFormatSetEnum::DATA_SET_SEVEN:
		return (checkedSet.seventhSet & formatID.dataFormat) == formatID.dataFormat;
	case DataFormatSetEnum::DATA_SET_UNKNOWN:
	default:
		throw std::runtime_error("CheckFormatSupport Error: Program was given an erroneous used data format set value!");
	}
}
