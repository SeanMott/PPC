#pragma once

//defines scope keywords

#include <string>

namespace PPC::Decoder::Scope
{
	//defines a scope type
	enum class ScopeType
	{
		Global = 0,
		Local,
		Weak,

		Count
	};

	//maps a array
	static const uint64_t SCOPE_KEYWORD_STRS_LENGTH = (uint64_t)ScopeType::Count;
	static const char* SCOPE_KEYWORD_STRS[SCOPE_KEYWORD_STRS_LENGTH] =
	{ "global", "local", "weak" };

	//if it a scope keyword
	inline bool IsScopeKeyword(const char* keyword, uint32_t& arrayIndex, ScopeType& type)
	{
		//is it a dot directive
		for (uint32_t i = 0; i < SCOPE_KEYWORD_STRS_LENGTH; ++i)
		{
			if (!strcmp(keyword, SCOPE_KEYWORD_STRS[i]))
			{
				arrayIndex = i;
				type = (ScopeType)i;
				return true;
			}
		}

		return false;
	}
}