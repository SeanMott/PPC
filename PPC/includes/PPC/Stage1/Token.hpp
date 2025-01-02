#pragma once

//defines a Token

#include <PPC/Data/TranslationUnit.hpp>

#include <PPC/Logger.hpp>

#include <vector>

namespace PPC::Stage1
{
	//defines a token type
	enum class TokenType
	{
		Genaric = 0, //this is differant from a identifier and is just a general token we use that stores a blob of string data
		//this is used in earlier subpasses to handle stuff we don't want to parse yet.
		//we parse it out at a later pass when there's less to worry about

		//Identifier, //the identifier

		Literal_String, //the string literal

		Operator, //a operator in the syntax

		SingleLineComment, //a single line # comment
		BlockComment, //a block comment

		NewLine,

		Count
	};

	//defines a token
	struct Token
	{
		size_t lineCount = 1, charCount = 0;
		TokenType type = TokenType::Count;
		std::string data = "";
	};

	//lexes ASM into tokens
	std::vector<Token> LexTokens(const Data::TranslationUnit& tu);
}