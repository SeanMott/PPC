#pragma once

//defines a PPC Symbol

#include <PPCLibVenders/json.hpp>

#include <PPCLib/Data/Scope.hpp>
#include <PPCLib/Data/ObjectType.hpp>

namespace PPC::SymbolMap
{
	//defines a PPC Symbol parsed from the DTK Symbol file
	struct PPCSymbol
	{
		std::string identifier = ""; //the name of the symbol
		//the Symbol ID associated with the Symbol

		PPC::Data::ObjectType::ObjectType type = PPC::Data::ObjectType::ObjectType::None; //is it a object, function, or label
		PPC::Data::Scope::ScopeType scope = PPC::Data::Scope::ScopeType::None; //the scope type

		std::string split = "", //the split section
			address = ""; //the address it starts

		std::string size = "NULL"; //the size

		std::string datatype = "NULL"; //the datatype

		//converts to a JSON Array
	};

	//dumps a stream of symbols to the file

	//loads a stream of symbols from a file
}