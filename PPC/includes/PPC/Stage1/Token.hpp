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
		Identifier = 0, //the identifier

		Literal_String, //the string literal

		//a single line # comment
		//a block comment

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