#pragma once

//defines various dot directives

#include <string>

namespace PPC::Decoder::DotDirectives
{
	//defines dot directives for keywords
	enum class DotDirective_Keyword
	{
		Include = 0,
		Filename,

		BAlign,

		Section,
		Section_Text,
		Section_Init,
		Section_Constructors,
		Section_Deconstructors,

		Hidden,

		FunctionStart,
		FunctionEnd,

		ObjectStart,
		ObjectEnd,

		JumpLabel,

		Count
	};

	//maps a array || we use jump label since it doesn't have a matching keyword but is still a dot directive
	static const uint64_t DOT_DIRECTIVE_KEYWORD_STRS_LENGTH = (uint64_t)DotDirective_Keyword::JumpLabel;
	static const char* DOT_DIRECTIVE_KEYWORD_STRS[DOT_DIRECTIVE_KEYWORD_STRS_LENGTH] =
	{ ".include", ".file", ".text",
	".section", ".text", ".init", ".ctors", ".dtors",
		".hidden",
	".fn", ".endfn",
	".obj", ".endobj" };

	//if it a dot directive keyword
	inline bool IsDotDirectiveKeyword(const char* keyword, uint32_t& arrayIndex, DotDirective_Keyword& keywordType)
	{
		//is it a dot directive
		for (uint32_t i = 0; i < DOT_DIRECTIVE_KEYWORD_STRS_LENGTH; ++i)
		{
			if (!strcmp(keyword, DOT_DIRECTIVE_KEYWORD_STRS[i]))
			{
				arrayIndex = i;
				keywordType = (DotDirective_Keyword)i;
				return true;
			}
		}

		//is it a jump label
		const size_t len = strnlen_s(keyword, SIZE_MAX);
		if (len > 2 && keyword[0] == '.' && keyword[len - 1] == ':')
		{
			arrayIndex = 0;
			keywordType = DotDirective_Keyword::JumpLabel;
			return true;
		}

		return false;
	}

	//defines dot directives for datatypes
	enum class DotDirective_Datatype
	{
		Byte = 0,
		Byte2,
		Skip_U16,

		Float,
		Double,
		
		String,
		Ascii,

		Byte4, //genaric byte4
		Byte4_FunctionPtr, //if the byte4 is a function pointer
		Byte4_Struct, //if the byte4 points to a struct
		Byte4_Invalid, //when a random invalid si found

		Count
	};

	//maps a array || we use Byte4_Invalid since it doesn't have a matching keyword but is still a dot directive datatype
	static const uint64_t DOT_DIRECTIVE_DATATYPE_STRS_LENGTH = (uint64_t)DotDirective_Datatype::Byte4_Invalid;
	static const char* DOT_DIRECTIVE_DATATYPE_STRS[DOT_DIRECTIVE_DATATYPE_STRS_LENGTH] =
	{ ".byte", ".2byte", ".skip", ".float", ".double", ".string", ".ascii", ".4byte", "funcPtr", "struct"};

	//if it a dot directive datatype
	inline bool IsDotDirectiveDatatype(const char* keyword, uint32_t& arrayIndex, DotDirective_Datatype& datatypeType)
	{
		//is it a dot directive
		for (uint32_t i = 0; i < DOT_DIRECTIVE_DATATYPE_STRS_LENGTH; ++i)
		{
			if (!strcmp(keyword, DOT_DIRECTIVE_DATATYPE_STRS[i]))
			{
				arrayIndex = i;
				datatypeType = (DotDirective_Datatype)i;
				return true;
			}
		}

		return false;
	}
}

namespace PPC::Decoder::BitDirectives
{
	//defines directives for manipulating low, high, or relative bit
	enum class BitDirectiveType
	{
		High = 0,
		Low,
		Relative,

		Count
	};

	//maps a array
	static const uint64_t BIT_DIRECTIVE_STRS_LENGTH = (uint64_t)BitDirectiveType::Count;
	static const char* BIT_DIRECTIVE_STRS[BIT_DIRECTIVE_STRS_LENGTH] =
	{ "ha", "l", "sda21" };

	//if it a bit directive
	inline bool IsBitDirective(const char* keyword, uint32_t& arrayIndex, BitDirectiveType& bitType)
	{
		//is it a bit directive
		for (uint32_t i = 0; i < BIT_DIRECTIVE_STRS_LENGTH; ++i)
		{
			if (!strcmp(keyword, BIT_DIRECTIVE_STRS[i]))
			{
				arrayIndex = i;
				bitType = (BitDirectiveType)i;
				return true;
			}
		}

		return false;
	}
}