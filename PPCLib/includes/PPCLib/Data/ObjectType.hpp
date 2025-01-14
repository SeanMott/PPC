#pragma once

//defines a object type

#include <string>

namespace PPC::Data::ObjectType
{
	//defines the object type
	enum class ObjectType
	{
		None = 0,

		Label_Sym,
		Function,
		Object
	};

	//converts a string keyword to a type
	static inline ObjectType ConvertDTKSymbolTypeIntoObjectType(const std::string& str)
	{
		if (str == "function")
			return ObjectType::Function;
		else if (str == "object")
			return ObjectType::Object;
		else if (str == "label")
			return ObjectType::Label_Sym;

		return ObjectType::None;
	}

	//checks for a .sym this is a called a label in the symbols....for some reason
	static inline bool CheckForASMKeyword_Sym(const char* str) { return (!strcmp(str, ".sym") ? true : false); }

}