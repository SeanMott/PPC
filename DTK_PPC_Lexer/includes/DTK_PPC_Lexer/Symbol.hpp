#pragma once

//defines functions for parsing and generating symbols

#define FMT_HEADER_ONLY
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/color.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/core.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/os.h"

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
		SymbolType type = SymbolType::Count; //type of symbol

		std::string name = "", //name of the symbol
			section = "", //the section it's from ie .init, .contor, .text, ect
			size = "", //the size in bytes of the symbol
			scope = "", //the scope of the symbol
			data = ""; //type of data if it's there
	};

	//parses a string of a symbol into a symbol
	inline Symbol GenerateSymbolFromStr(const std::string& line)
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

	//turns a symbol into a string symbol for a file

	//parses a symbol file


	//compares two symbol files, creating a list of differant entries by name
}