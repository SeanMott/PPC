#pragma once

//defines the scoping for objects and functions

#include <string>

namespace PPC::Data::Scope
{
	//defines a scope type
	enum class ScopeType
	{
		None = 0, //if not found

		//types used in symbols and ASM
		Global,
		Local,
		Weak,

		Hidden, //type used in ASM

		Count
	};

	//converts a string keyword to a scope type
	static inline ScopeType ConvertDTKKeywordStringToScopeType(const std::string& str)
	{
		if (str == "global")
			return ScopeType::Global;
		else if (str == "local")
			return ScopeType::Local;
		else if (str == "weak")
			return ScopeType::Weak;
		else if (str == ".hidden")
			return ScopeType::Hidden;

		return ScopeType::None;
	}

	//checks if it's a scope keyword
	static inline bool IsScopeKeyword(const std::string& str, ScopeType& type)
	{
		type = ConvertDTKKeywordStringToScopeType(str);
		return (type != ScopeType::None ? true : false);
	}
}