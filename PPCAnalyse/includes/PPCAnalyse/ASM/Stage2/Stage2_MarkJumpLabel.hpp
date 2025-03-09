#pragma once

//defines a jump label

#include <PPCLib/Token/Token.hpp>

namespace PPC::Analyse::ASM::Stage2::Subpass
{
	inline void PerformSubpass_MarkJumpLabels(std::vector<PPC::Token::Token>& tokens)
	{
		//get the jump labels
		size_t tokenCount = tokens.size();
		for (size_t i = 0; i < tokenCount; ++i)
		{
			if (i + 1 < tokenCount && tokens[i].type == PPC::Token::TokenType::Genaric && tokens[i].data.size() > 2 && tokens[i].data[0] == '.' &&
				tokens[i + 1].type == PPC::Token::TokenType::Operator && tokens[i + 1].data == ":")
			{
				tokens[i].type = PPC::Token::TokenType::JumpLabel;
				tokenCount--; tokens.erase(tokens.begin() + i + 1);
			}
		}
	}
}