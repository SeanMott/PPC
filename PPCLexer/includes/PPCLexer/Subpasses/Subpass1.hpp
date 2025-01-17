#pragma once

//defines the first subpass for lexing
//this takes raw ASM and converts it to a stream of tokens

#include <PPCLib/Token/Token.hpp>

#include <string>
#include <vector>

namespace PPC::Stage1
{
	//defines a parser
	struct Parser
	{
		size_t lineCount = 1, charCount = 0,
			codeIndex = 0, codeLength = 0;
		std::string code = "";

		//sets the code
		inline void Parser_SetCodeForParsing(const std::string rawCode)
		{
			code = rawCode;
			codeLength = rawCode.size();
			codeIndex = 0;
			lineCount = 1;
			charCount = 0;
		}

		//gets the next char
		inline char Parser_GetNextChar()
		{
			if (codeIndex + 1 >= codeLength)
				return -1;

			codeIndex++;
			return code[codeIndex];
		}

		//peeks the next char
		inline char Parser_PeekNextChar()
		{
			if (codeIndex + 1 >= codeLength)
				return -1;

			return code[codeIndex + 1];
		}
	};

	//parses raw code into Genaric Tokens for Subpass 1
	//read the Subpass 1: Genaric Token Splits in the README
	std::vector<PPC::Stage1::Token> Subpass1_GenerateGeneralTokens(const std::string& rawCode);
}