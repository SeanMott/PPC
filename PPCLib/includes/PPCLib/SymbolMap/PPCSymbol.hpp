#pragma once

//defines a PPC Symbol

#include <PPCLibVenders/json.hpp>

#include <PPCLib/Data/Scope.hpp>
#include <PPCLib/Data/ObjectType.hpp>

#include <filesystem>
#include <fstream>

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
		inline nlohmann::json GenerateJSONArrayEntry() const
		{
			return nlohmann::json{ {"symbolName", identifier}, {"split", split}, {"address", address},
				{"size", size}, {"datatype", datatype}, {"scope", scope} };
		}
	};

	//dumps a stream of symbols to the file
	static inline void DumpPPCSymbolsToMap(const std::filesystem::path& ppcMap, const std::vector<PPCSymbol>& symbols)
	{
		nlohmann::json ppcMapSymbols = nlohmann::json::array();
		for (size_t i = 0; i < symbols.size(); ++i)
			ppcMapSymbols.emplace_back(symbols[i].GenerateJSONArrayEntry());
		std::ofstream file(ppcMap);
		file << ppcMapSymbols.dump();
	}

	//loads a stream of symbols from a file
}