#pragma once

//fine types the registers, instructions, memory offsets, scoping, pre-defined keywords
//and datatypes

#include <PPCLib/Token/Token.hpp>

#include <PPCLib/Data/Registers/ConditionRegister.hpp>
#include <PPCLib/Data/Registers/IntegerRegister.hpp>
#include <PPCLib/Data/Registers/FloatingRegisters.hpp>
#include <PPCLib/Data/Registers/SpecialRegister.hpp>
#include <PPCLib/Data/Registers/GraphicsQuantizedRegisters.hpp>

#include <PPCLib/Data/PPCInstructions.hpp>

#include <PPCLib/Data/GeneralKeywords.hpp>

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

			PPC::Data::Scope::ScopeType scopeType = PPC::Data::Scope::ScopeType::None;
			PPC::Data::MemoryOffset::MemoryOffsetType memoryOffsetType = PPC::Data::MemoryOffset::MemoryOffsetType::None;
			PPC::Data::Datatype::DTKDatatypeType datatype = PPC::Data::Datatype::DTKDatatypeType::None;

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

				//checks for a scoping
				else if (PPC::Data::Scope::IsScopeKeyword(generalTokens[i].data.c_str(), scopeType))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword_Scope;
					generalTokens[i].scopeType = scopeType;
				}

				//---memory offsets

				else if (PPC::Data::MemoryOffset::IsASMKeyword_MemoryOffset(generalTokens[i].data.c_str(), memoryOffsetType))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Keyword_MemoryOffset;
					generalTokens[i].memoryOffsetType = memoryOffsetType;
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
				else if (Data::Datatype::IsASMKeyword_Datatype(generalTokens[i].data.c_str(), datatype))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Datatype;
					generalTokens[i].datatype = datatype;
				}

				//if it's assembly instruction
				else if (PPC::Data::ASM::IsASMInstructionStr(generalTokens[i].data.c_str(), instArrayIndex, ppcInstrct))
				{
					generalTokens[i].type = PPC::Stage1::TokenType::Instruction;
					generalTokens[i].instruction = ppcInstrct;
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