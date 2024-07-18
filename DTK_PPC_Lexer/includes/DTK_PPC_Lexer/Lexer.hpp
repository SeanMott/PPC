#pragma once

//defines a lexer for parsing DTK Assembly

#define FMT_HEADER_ONLY
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/color.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/core.h"

#include <DTK_PowerPCDecoder/AssemblyInstructions.hpp>
#include <DTK_PowerPCDecoder/Registers.hpp>

#include <string>
#include <vector>

namespace PPC::Frontend::DTK
{
	//defines a token type
	enum class TokenType
	{
		Identifier = 0,

		Comment_ASMIntel,
		Comment_ASMInstructionAddress,

		Literal_Integer,
		Literal_Float,
		Literal_Hex,
		Literal_String,

		Register_Int,
		Register_Float,
		Register_Keyword,

		DotDirective_Keyword,
		DotDirective_Datatype,

		Operator,

		ASMInstruction,

		ScopeKeyword,

		Count
	};


	//defines a token
	struct Token
	{
		TokenType type = TokenType::Count;
		size_t lineCount = 0;
		std::string data = "";

		//prints data
		void Print();
	};

	//defines a parser for DTK Assembly
	std::vector<Token> ASMParser(const std::string& code);
}