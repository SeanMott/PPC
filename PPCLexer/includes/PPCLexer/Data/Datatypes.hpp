#pragma once

//defines the datatypes

#include <string>

//lists the datatypes
#define PPC_LEXER_DATATYPE_COUNT 8
static const char* PPC_LEXER_DATATYPE_STRINGS[PPC_LEXER_DATATYPE_COUNT] = {
	".skip", ".4byte", ".2byte", ".byte", ".double", ".float", ".string", ".rel"
};

//checks if it's a datatype
static inline bool Subpass2_IsDatatype(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_DATATYPE_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_DATATYPE_STRINGS[i]))
			return true;
	}

	return false;
}
