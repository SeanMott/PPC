#pragma once

//defines datatypes used accros the tools

#include <string>

namespace PPC::Data::Datatype
{
	//defines a datatype in DTK
	enum class DTKDatatypeType
	{
		None = 0,

		Skip, //a skip datatype, we normally use it as space reserving. We map it to a uint32
		Byte4, //this can generally be anything, either a uint16 or a void*
		Byte2, //double of a char
		Byte, //this is a char

		Float, //it's a float
		Double, //it's a double floating

		String, //a string

		Rel, //defines a relocation
	};

	//lists the datatypes for DTK Assembly
#define DTK_KEYWORD_DATATYPE_STRINGS_COUNT 8
	static const char* DTK_KEYWORD_DATATYPE_STRINGS[DTK_KEYWORD_DATATYPE_STRINGS_COUNT] = {
		".skip", ".4byte", ".2byte", ".byte", ".float", ".double", ".string", ".rel"
	};

	//checks if the ASM is a DTK datatype
	static inline bool IsASMKeyword_Datatype(const char* key, DTKDatatypeType& type)
	{
		for (size_t i = 0; i < DTK_KEYWORD_DATATYPE_STRINGS_COUNT; ++i)
		{
			if (!strcmp(key, DTK_KEYWORD_DATATYPE_STRINGS[i]))
			{
				type = (DTKDatatypeType)i;
				return true;
			}
		}

		type = DTKDatatypeType::None;
		return false;
	}
}