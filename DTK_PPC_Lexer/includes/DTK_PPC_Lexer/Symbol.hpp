#pragma once

//defines functions for parsing and generating symbols

#define FMT_HEADER_ONLY
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/color.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/core.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/os.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace PPC::Frontend::DTK::Symbol
{
	//defines a symbol type
	enum class SymbolType
	{
		Function = 0,
		Object,
		Label,

		Count
	};

	//defines a symbol
	struct Symbol
	{
		bool hasBeenRenamed = false; //marks this symbol as needing to be renamed

		SymbolType type = SymbolType::Count; //type of symbol

		std::string name = "", //name of the symbol
			section = "", //the section it's from ie .init, .contor, .text, ect
			size = "", //the size in bytes of the symbol
			scope = "", //the scope of the symbol
			data = ""; //type of data if it's there

		//formats a string for post PPC symbol cache
		inline std::string FormatStringForPPCSymbolData()
		{
			std::string s = name + ", ";
			switch (type)
			{
			case SymbolType::Object:
				s += "object";
				break;

			case SymbolType::Function:
				s += "function";
				break;

			case SymbolType::Label:
				s += "label";
				break;
			}

			s += "\n";
			return s;
		}
	};

	//parses a string of a symbol into a symbol
	inline Symbol GenerateSymbolFrom_DTKSymbolStr(const std::string& line)
	{
		Symbol s;

		std::string data = "";
		for (size_t c = 0; c < line.size(); ++c)
		{
			if (line[c] == ' ' || line[c] == '\n')
			{
				//check what part of the string we are in
				fmt::print(" {} ", data);
				data = "";
				continue;
			}

			data += line[c];
		}

		fmt::print("\n");

		return s;
	}

	//parses a whole DTK symbol file
	inline std::vector<Symbol> GenerateSymbolsFrom_DTKSymbolFile(const std::string& symbolFilepath)
	{
		std::vector<PPC::Frontend::DTK::Symbol::Symbol> symbols; symbols.reserve(200);
		std::ifstream input(symbolFilepath);
		for (std::string line; getline(input, line); )
		{
			PPC::Frontend::DTK::Symbol::Symbol symbol;
			//splits line
			const size_t lineCount = line.size();
			std::vector<std::string> parts; parts.reserve(5);
			std::string data = "";
			for (size_t i = 0; i < lineCount; ++i)
			{
				if (line[i] == ' ' || line[i] == '\n')
				{
					parts.emplace_back(data);
					data = "";
					continue;
				}

				data += line[i];
			}

			//gets the name, always 0
			symbol.name = parts[0];

			//searches for the type
			for (uint32_t i = 4; i < parts.size(); ++i)
			{
				if (!strcmp("type:object", parts[i].c_str()))
				{
					symbol.type = PPC::Frontend::DTK::Symbol::SymbolType::Object;
					break;
				}
				else if (!strcmp("type:function", parts[i].c_str()))
				{
					symbol.type = PPC::Frontend::DTK::Symbol::SymbolType::Function;
					break;
				}
				else if (!strcmp("type:label", parts[i].c_str()))
				{
					symbol.type = PPC::Frontend::DTK::Symbol::SymbolType::Label;
					break;
				}

				fmt::print("part {}: {} || ", i, parts[i]);
				fmt::print("\n");
			}

			symbols.emplace_back(symbol);
		}

		return symbols;
	}

	//writes a PPC symbol file

	//creates a PPC symbol from a line

	//creates a list of PPC symbols from a PPC symbol file
}