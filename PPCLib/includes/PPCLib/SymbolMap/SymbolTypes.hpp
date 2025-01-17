#pragma once

//some symbols have unique names that aren't a normal type DTK generates in the Assemly.
//We factor this out by having a uniqie symbol type we parse out for

#include <string>

namespace PPC::SymbolMap
{
	//defines types in the symbol map
#define SYMBOL_MAP_TYPES_STR_COUNT 7
	const char* SYMBOL_MAP_TYPES_STR[SYMBOL_MAP_TYPES_STR_COUNT] = {
		"NULL", "4byte", "2byte", "byte", "string", "double", "float"
	};

	//defines their types
	enum class SymbolMapType
	{
		Null = 0,

		Byte4,
		Byte2,
		Byte,

		String,

		Double,
		Float
	};

	//checks for symbol types
	inline bool IsSymbolMapType(const char* str, SymbolMapType& type)
	{
		for (size_t i = 0; i < SYMBOL_MAP_TYPES_STR_COUNT; ++i)
		{
			if (!strcmp(str, SYMBOL_MAP_TYPES_STR[i]))
			{
				type = (SymbolMapType)i;
				break;
			}
		}

		return (type == SymbolMapType::Null ? false : true);
	}
}