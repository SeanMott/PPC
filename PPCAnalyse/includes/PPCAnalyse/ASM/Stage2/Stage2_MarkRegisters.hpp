#pragma once

//marks register tokens

#include <PPCLib/Token/Token.hpp>


namespace PPC::Analyse::ASM::Stage2::Subpass
{
	inline void PerformSubpass_MarkRegisters(std::vector<PPC::Token::Token>& tokens)
	{
		//gets the register
		size_t tokenCount = tokens.size();
		for (size_t i = 0; i < tokenCount; ++i)
		{
			if (tokens[i].type == PPC::Token::TokenType::Genaric)
			{
				if (Subpass2_IsConditionRegister(tokens[i].data.c_str()))
				{
					tokens[i].type = PPC::Token::TokenType::Register;
					tokens[i].specificType = PPC::Token::SpecificTokenType::Register_Condition;
				}
				else if (Subpass2_IsSpecialRegister(tokens[i].data.c_str()))
				{
					tokens[i].type = PPC::Token::TokenType::Register;
					tokens[i].specificType = PPC::Token::SpecificTokenType::Register_Special;
				}
				else if (Subpass2_IsGraphicsQuantizedRegister(tokens[i].data.c_str()))
				{
					tokens[i].type = PPC::Token::TokenType::Register;
					tokens[i].specificType = PPC::Token::SpecificTokenType::Register_GraphicsQuantized;
				}
				else if (Subpass2_IsFloatingRegister(tokens[i].data.c_str()))
				{
					tokens[i].type = PPC::Token::TokenType::Register;
					tokens[i].specificType = PPC::Token::SpecificTokenType::Register_Float;
				}
				else if (Subpass2_IsIntegerRegister(tokens[i].data.c_str()))
				{
					tokens[i].type = PPC::Token::TokenType::Register;
					tokens[i].specificType = PPC::Token::SpecificTokenType::Register_Int;
				}
			}
		}
	}
}