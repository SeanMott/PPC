#pragma once

//defines the scoping for objects and functions

#include <string>

namespace PPC::Data::Scope
{
	//defines a scope type
	enum class ScopeType
	{
		None = 0,

		Global,
		Local,
		Weak,

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

		return ScopeType::None;
	}
}