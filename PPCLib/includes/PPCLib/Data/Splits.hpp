#pragma once

//defines a split section

#include <string>

namespace PPC::Data::Split
{
		//defines the section split name
		enum class SectionSplit
	{
		Init = 0,
		Text,
		CTors,
		DTors,
		Rodata,
		Data,
		BSS,
		SData,
		SBss,
		SData2,

		Count
	};

		//defines the type
	enum class Type
	{
		Code = 0,
		Rodata,
		Data,
		Bss,

		Count
	};

		//converts a section to it's type

		//returns the alignment of the section
}

//defines functions for parsing DTK Assembly
namespace PPC::Parsing::DTK
{
	/*
		.init       type:code align:4
		.text       type:code align:4
		.ctors      type:rodata align:16
		.dtors      type:rodata align:32
		.rodata     type:rodata align:32
		.data       type:data align:16
		.bss        type:bss align:32
		.sdata      type:data align:16
		.sbss       type:bss align:8
		.sdata2     type:rodata align:32
	*/

	//lists all the split sections keyword strings
#define PPC_LIB_PARSING_DTK_SPLIT_KEYWORD_STRING_COUNT 10
	static const char* PPC_LIB_PARSING_DTK_SPLIT_KEYWORD_STRINGS[PPC_LIB_PARSING_DTK_SPLIT_KEYWORD_STRING_COUNT] = {
		".init",
		".text",
		".ctors",
		".dtors",
		".rodata",
		".data",
		".bss",
		".sdata",
		".sbss",
		".sdata2"
	};

	//checks if it's a split section
	static inline bool IsDTKKeyword_Split(const char* str)
	{
		for (size_t i = 0; i < PPC_LIB_PARSING_DTK_SPLIT_KEYWORD_STRING_COUNT; ++i)
		{
			if (!strcmp(str, PPC_LIB_PARSING_DTK_SPLIT_KEYWORD_STRINGS[i]))
				return true;
		}

		return false;
	}
}