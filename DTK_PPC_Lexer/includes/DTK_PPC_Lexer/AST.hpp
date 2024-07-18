#pragma once

//defines a AST node types

#include <DTK_PPC_Lexer/Lexer.hpp>
#include <DTK_PPC_Lexer/Symbol.hpp>

#define FMT_HEADER_ONLY
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/color.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/core.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/os.h"

namespace PPC::Frontend::DTK
{
	//defines a AST node type
	enum class ASTNodeType
	{
		Identifier,

		DotDirective,
		BitDirective,

		Variable,

		ASMInstruction,

		Literal_Integer,
		Literal_Float,
		Literal_Hex,
		Literal_String,

		Register_Int,
		Register_Float,
		Register_Keyword,

		Function,
		Struct,

		Count
	};

	//defines dot derective node metadata

	//defines register node metadata

	//defines a constant node metadata

	//defines a variable node metadata
	struct ASTNodeMetadat_Var
	{
		PPC::Decoder::DotDirectives::DotDirective_Datatype datatype = PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte2;

		bool isValueTokensALiteral = false; //is value token a literal
		bool isValueTokensAIdentifier = false; //is value token a identifier
		bool isValueTokensSeveralTokens = false; //is value token several tokens
		bool valueTokensContainsAFucntion = false; //the value tokens for this variable contains a name matching a function symbol
		bool valueTokensContainsAStruct = false; //the value tokens for this variable contains a name matching a struct symbol
		bool valueTokensContainsALabel = false; //the value tokens for this variable contains a name matching a label symbol

		std::vector<PPC::Frontend::DTK::Token> valueTokens; //value tokens
	};

	//defines a struct node metadata
	struct ASTNodeMetadat_Struct
	{
		bool isHidden = false; //is it hidden
		bool nameWasInAString = false; //was the name in "", this is done if it starts with a @
		PPC::Decoder::Scope::ScopeType scope = PPC::Decoder::Scope::ScopeType::Global;
		std::string structName = "";

		std::vector<ASTNodeMetadat_Var> variables; //variables
	};

	//defines a ASM instruction node metadata

	//defines a jump label node metadata

	//defines a function node metadata

	//defines a AST node
	struct ASTNode
	{
		ASTNodeType type = ASTNodeType::Count;

		//metadata
		ASTNodeMetadat_Struct structMetadata;

		//prints data
		void Print() const
		{
			switch (type)
			{
			case ASTNodeType::Struct:
				//prints name prototype
				fmt::print(fmt::fg(fmt::color::purple), "(isHidden: {}) ",
					structMetadata.isHidden);
				fmt::print(fmt::fg(fmt::color::dark_orchid), "(scope: {}) ",
					PPC::Decoder::Scope::SCOPE_KEYWORD_STRS[(uint32_t)structMetadata.scope]);
				fmt::print(fmt::fg(fmt::color::coral), "struct {} \n",
					structMetadata.structName.c_str());

				//prints variables
				for (size_t v = 0; v < structMetadata.variables.size(); ++v)
				{
					fmt::print(fmt::fg(fmt::color::fire_brick), "---Datatype {} ||",
						PPC::Decoder::DotDirectives::DOT_DIRECTIVE_DATATYPE_STRS[(uint64_t)structMetadata.variables[v].datatype]);
					for(uint32_t d = 0; d < structMetadata.variables[v].valueTokens.size(); ++d)
					fmt::print(fmt::fg(fmt::color::cadet_blue), " {} ",
						structMetadata.variables[v].valueTokens[d].data);
					fmt::print("\n\n");
				}

				break;

			default:
				break;
			}
		}
	};

	//generates AST tree
	std::vector<ASTNode> GenerateAST(const std::vector<Token>& tokens, const std::vector<Symbol::Symbol>& symbols);

	//generates struct definitions only

	//generate function definitions only
	
}