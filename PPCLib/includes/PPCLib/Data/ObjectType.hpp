#pragma once

//defines a object type

#include <string>

namespace PPC::Data::ObjectType
{
	//defines the object type
	enum class ObjectType
	{
		None = 0,

		//for symbols
		Label_Sym,
		Function,
		Object,

		//for ASM
		Object_Start,
		Object_End,

		Func_Start,
		Func_End
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

	//check for ASM Object Keyword
	static inline bool IsASMObjectKeyword(const char* str, ObjectType& type)
	{
		if (!strcmp(str, ".sym"))
		{
			type = ObjectType::Label_Sym;
			return true;
		}

		else if (!strcmp(str, ".obj"))
		{
			type = ObjectType::Object_Start;
			return true;
		}
		else if (!strcmp(str, ".endobj"))
		{
			type = ObjectType::Object_End;
			return true;
		}

		else if (!strcmp(str, ".fn"))
		{
			type = ObjectType::Func_Start;
			return true;
		}
		else if (!strcmp(str, ".endfn"))
		{
			type = ObjectType::Func_End;
			return true;
		}

		type = ObjectType::None;
		return false;
	}
}