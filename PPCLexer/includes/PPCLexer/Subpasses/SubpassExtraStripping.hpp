#pragma once

#include <PPCLexer/Token.hpp>

//defines the second subpass, this removes invalid and illegal instructions
//optionally strips out all comments

namespace PPC::Lexer::Subpass
{
	//defines a line of tokens
	struct TokenLine
	{
		std::vector<PPC::Stage1::Token> tokens;
	};

	//defines a token stream defining a function

	//defines a token stream defining a struct

	//defines a token stream file
	struct TokenStreamFile
	{
		std::vector<PPC::Stage1::Token> wholeFileTokens; //defines the remaining total
	};


	//removes the invalid and illegal instrucitons
	static inline std::vector<PPC::Stage1::Token> ExtraSubpass_RemoveInvalidInstructions(std::vector<PPC::Stage1::Token>& subpass1Tokens)
	{
		const size_t subpass1TokenCount = subpass1Tokens.size();
		std::vector<PPC::Stage1::Token> tokens;
		tokens.reserve(subpass1TokenCount);

		//compress the tokens into the new tree
		for (size_t i = 0; i < subpass1TokenCount; ++i)
		{
			//check for this line and the next few to be invalid or illegal structure and skip it all if so
			if (i + 3 < subpass1TokenCount && subpass1Tokens[i].type == PPC::Stage1::TokenType::BlockComment && subpass1Tokens[i + 1].type == PPC::Stage1::TokenType::Datatype &&
				subpass1Tokens[i + 2].type == PPC::Stage1::TokenType::Identifier && subpass1Tokens[i + 3].type == PPC::Stage1::TokenType::BlockComment &&
				subpass1Tokens[i + 3].data == " invalid " ||
				i + 3 < subpass1TokenCount && subpass1Tokens[i].type == PPC::Stage1::TokenType::BlockComment && subpass1Tokens[i + 1].type == PPC::Stage1::TokenType::Datatype &&
				subpass1Tokens[i + 2].type == PPC::Stage1::TokenType::Identifier && subpass1Tokens[i + 3].type == PPC::Stage1::TokenType::BlockComment &&
				subpass1Tokens[i + 3].data.find("illegal:"))
			{
				i += 4; //we add the extra bit to skip the new line
				continue;
			}

			tokens.emplace_back(subpass1Tokens[i]);
		}

		return tokens;
	}

	//option extra pass that removes ALL comments and section based tokens
	static inline std::vector<PPC::Stage1::Token> ExtraSubpass_StripCommentsAndSectors(std::vector<PPC::Stage1::Token>& subpassTokens)
	{
		const size_t subpassTokenCount = subpassTokens.size();
		std::vector<PPC::Stage1::Token> tokens;
		tokens.reserve(subpassTokenCount);

		//compress the tokens into the new tree
		for (size_t i = 0; i < subpassTokenCount; ++i)
		{
			//if we're .section,.file or .include or .data remove the whole line
			if (subpassTokens[i].type == PPC::Stage1::TokenType::Identifier && subpassTokens[i].data == ".section" ||
				subpassTokens[i].type == PPC::Stage1::TokenType::Identifier && subpassTokens[i].data == ".include" ||
				subpassTokens[i].type == PPC::Stage1::TokenType::Identifier && subpassTokens[i].data == ".file" ||
				subpassTokens[i].type == PPC::Stage1::TokenType::Identifier && subpassTokens[i].data == ".data" ||
				subpassTokens[i].type == PPC::Stage1::TokenType::Identifier && subpassTokens[i].data == ".text")
			{
				while (subpassTokens[i].type != PPC::Stage1::TokenType::NewLine && i < subpassTokenCount)
				{
					i++;
				}

				continue;
			}

			//removes comment
			else if (subpassTokens[i].type == PPC::Stage1::TokenType::BlockComment || subpassTokens[i].type == PPC::Stage1::TokenType::SingleLineComment)
				continue;

			//adds token
			tokens.emplace_back(subpassTokens[i]);
		}

		return tokens;
	}
}