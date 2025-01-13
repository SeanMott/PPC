#pragma once

//fine types the registers, instructions, memory offsets, scoping, pre-defined keywords
//and datatypes

#include <PPCLexer/Token.hpp>

#include <PPCLexer/Data/ConditionRegister.hpp>
#include <PPCLexer/Data/IntegerRegister.hpp>
#include <PPCLexer/Data/FloatingRegisters.hpp>
#include <PPCLexer/Data/SpecialRegister.hpp>
#include <PPCLexer/Data/GraphicsQuantizedRegisters.hpp>

#include <PPCLexer/Data/Datatypes.hpp>
#include <PPCLexer/Data/MemoryOffset.hpp>
#include <PPCLexer/Data/PPCInstructions.hpp>
#include <PPCLexer/Data/Scoping.hpp>

#include <PPCLexer/Data/GeneralKeywords.hpp>

namespace PPC::Lexer::Subpass
{
	//defines the subpass 2 for fine typing tokens after inital typing
	static inline std::vector<Stage1::Token> Subpass2_GenerateFineTyping(std::vector<Stage1::Token>& generalTokens)
	{
		std::vector<Stage1::Token> tokens;
		const size_t generalTokenCount = generalTokens.size();
		tokens.reserve(generalTokenCount);

		for (size_t i = 0; i < generalTokenCount; ++i)
		{
			uint32_t instArrayIndex = 0;
			PPC::Data::ASM::EInstruction ppcInstrct;

			//if it's a general token
			if (generalTokens[i].type == Stage1::TokenType::Genaric)
			{
				//if it's a aligment keyword
				if (Subpass2_IsKeyword_Alignment(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Alignment;
				}

				//---scoping

				//if it's a global scope keyword
				else if (Subpass2_IsKeyword_Scope_Global(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Global;
				}

				//if it's a local scope keyword
				else if (Subpass2_IsKeyword_Scope_Local(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Local;
				}

				//if it's a weak scope keyword
				else if (Subpass2_IsKeyword_Scope_Weak(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Weak;
				}

				//if it's a hidden scope keyword
				else if (Subpass2_IsKeyword_Scope_Hidden(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Hidden;
				}

				//if it's a sym scope keyword
				else if (Subpass2_IsKeyword_Scope_Sym(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Sym;
				}

				//---memory offsets

				//if it's a sda21 memory offset keyword
				else if (Subpass2_IsKeyword_MemoryOffset_Sda21(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_Sda21;
				}

				//if it's a lower bit memory offset keyword
				else if (Subpass2_IsKeyword_MemoryOffset_LowerBit(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_LowerBit;
				}

				//if it's a higher bit memory offset keyword
				else if (Subpass2_IsKeyword_MemoryOffset_HigherBit(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_HigherBit;
				}

				//---registers
				
				//if it's a int register
				else if (Subpass2_IsIntegerRegister(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Register;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Int;
				}

				//if it's a floating register
				else if (Subpass2_IsFloatingRegister(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Register;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Float;
				}

				//if it's a graphics quantized register
				else if (Subpass2_IsGraphicsQuantizedRegister(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Register;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_GraphicsQuantized;
				}

				//if it's a condition register
				else if (Subpass2_IsConditionRegister(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Register;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Condition;
				}

				//if it's a special register
				else if (Subpass2_IsSpecialRegister(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Register;
					generalTokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Special;
				}

				//--general keywords

				//---other

				//if it's a datatype
				else if (Subpass2_IsDatatype(generalTokens[i].data.c_str()))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Datatype;
				}

				//if it's assembly instruction
				else if (PPC::Data::ASM::IsASMInstructionStr(generalTokens[i].data.c_str(), instArrayIndex, ppcInstrct))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Instruction;
				}

				//if it's a digit literal

				//else it's a Identifier
				else
					generalTokens[i].type = PPC::Stage1::TokenType::Identifier;
			}

			//add it to the tree
			tokens.emplace_back(generalTokens[i]);
		}


		return tokens;
	}
}