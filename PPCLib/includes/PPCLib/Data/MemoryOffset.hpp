#pragma once

//defines memory offsets

#include <string>

namespace PPC::Data::MemoryOffset
{
	//defines a memory offset
	enum class MemoryOffsetType
	{
		None = 0,

		Sda21,
		LowerBit,
		HigherBit
	};

	//converts a memory offset keyword to a memory offset type
	static inline MemoryOffsetType ConvertDTKKeywordStringToMemoryOffsetType(const char* keyword)
	{
		if (!strcmp(keyword, "sda21"))
			return MemoryOffsetType::Sda21;
		else if (!strcmp(keyword, "l"))
			return MemoryOffsetType::LowerBit;
		else if (!strcmp(keyword, "ha"))
			return MemoryOffsetType::HigherBit;

		return MemoryOffsetType::None;
	}

	//checks if it's a memory offset keyword
	static inline bool IsASMKeyword_MemoryOffset(const char* str, MemoryOffsetType& type)
	{
		type = ConvertDTKKeywordStringToMemoryOffsetType(str);
		return (type != MemoryOffsetType::None ? true : false);
	}
}