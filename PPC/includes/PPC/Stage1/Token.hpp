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

		//Identifier, //the identifier

		Keyword, //a keyword

		//Datatype, //a datatype

		//Register, //a register

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
		//defines a func start definition token
		//defines a func end definition token
		//defines a func name token

		//defines a object start definition token
		//defines a object end definition token
		//defines a object name token

		//defines a scope keyword || global, local, or weak

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
			}
		}
	};

	//lexes ASM into tokens
	std::vector<Token> LexTokens(const Data::TranslationUnit& tu);
}