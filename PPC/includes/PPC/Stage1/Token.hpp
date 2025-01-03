#pragma once

//defines a Token

#include <PPC/Data/TranslationUnit.hpp>

#include <PPC/Logger.hpp>

#include <vector>

namespace PPC::Stage1
{
	//defines a general token type
	enum class TokenType
	{
		Genaric = 0, //this is differant from a identifier and is just a general token we use that stores a blob of string data
		//this is used in earlier subpasses to handle stuff we don't want to parse yet.
		//we parse it out at a later pass when there's less to worry about

		Identifier, //the identifier

		Keyword, //a keyword

		Datatype, //a datatype

		Register, //a register

		JumpLabelDefinition, //marks the definition of a jump label

		Literal_String, //the string literal

		Operator, //a operator in the syntax

		SingleLineComment, //a single line # comment
		BlockComment, //a block comment

		NewLine,

		Count
	};

	//defines a specific token type
	enum class SpecificTokenType
	{
		//func
		Keyword_FuncStart = 0, //defines a func start definition token
		Keyword_FuncEnd, //defines a func end definition token

		//object
		Keyword_ObjStart, //defines a object start definition token
		Keyword_ObjEnd, //defines a object end definition token

		//scope
		Keyword_Scope_Global,
		Keyword_Scope_Local,
		Keyword_Scope_Weak,
		Keyword_Scope_Hidden,
		Keyword_Scope_Sym,

		//memory offset
		Keyword_MemoryOffset_Sda21,
		Keyword_MemoryOffset_LowerBit,
		Keyword_MemoryOffset_HigherBit,

		//mic
		Keyword_Alignment,

		//registers
		Register_Int, //if it's a int register
		Register_Float,
		Register_GraphicsQuantized,
		Register_Condition,
		Register_Special,

		Count
	};

	//defines a token
	struct Token
	{
		size_t lineCount = 1, charCount = 0;
		TokenType type = TokenType::Count; //the general type
		SpecificTokenType specificType = SpecificTokenType::Count; //the specific type
		std::string data = "";

		//prints the token
		inline void Print() const
		{
			switch (type)
			{
			case TokenType::Genaric:
				fmt::print("Line: {}, Char: {} || {}\n", lineCount, charCount, data);
				break;

			case TokenType::Keyword:
				fmt::print("Line: {}, Char: {} || Keyword || {}\n", lineCount, charCount, data);
				break;

			case TokenType::Datatype:
				fmt::print("Line: {}, Char: {} || Datatype || {}\n", lineCount, charCount, data);
				break;

			case TokenType::Register:
				fmt::print("Line: {}, Char: {} || Register || {}\n", lineCount, charCount, data);
				break;

			case TokenType::JumpLabelDefinition:
				fmt::print("Line: {}, Char: {} || Jump Label || {}\n", lineCount, charCount, data);
				break;

			case TokenType::Identifier:
				fmt::print(fmt::fg(fmt::color::blue), "Line: {}, Char: {} || Identifier {}\n", lineCount, charCount, data);
				break;
			}
		}
	};

	//lexes ASM into tokens
	std::vector<Token> LexTokens(const Data::TranslationUnit& tu);
}