#pragma once

//defines a lexer for parsing DTK Assembly

#define FMT_HEADER_ONLY
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/color.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/core.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/os.h"

#include <DTK_PowerPCDecoder/AssemblyInstructions.hpp>
#include <DTK_PowerPCDecoder/Registers.hpp>
#include <DTK_PowerPCDecoder/DotDirectives.hpp>
#include <DTK_PowerPCDecoder/ScopeKeywords.hpp>

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
		BitDirective,

		Operator,

		ASMInstruction,

		ScopeKeyword,

		Newline,

		Count
	};


	//defines a token
	struct Token
	{
		//genaric data
		TokenType type = TokenType::Count;
		size_t lineCount = 0;
		std::string data = "";

		//specific data
		uint32_t arrayIndex = 0;
		PPC::Decoder::ASM::EInstruction instruction;
		PPC::Decoder::Register::IntegerGeneralPurposeRegister intRegister; PPC::Decoder::Register::FloatingGeneralPurposeRegister floatRegister;
		PPC::Decoder::Register::Register_Keword_Enum keywordRegister;
		PPC::Decoder::DotDirectives::DotDirective_Keyword dotDirective;
		PPC::Decoder::DotDirectives::DotDirective_Datatype datatype;
		PPC::Decoder::BitDirectives::BitDirectiveType bitDirective;
		PPC::Decoder::Scope::ScopeType scope;

		//prints data
		std::string Print() const;

		//generates DTK valid assembly
		std::string GenerateDTKAssembly() const;
	};

	//defines a parser for DTK Assembly into lexed tokens
	std::vector<Token> ASMParser(const std::string& code);
}