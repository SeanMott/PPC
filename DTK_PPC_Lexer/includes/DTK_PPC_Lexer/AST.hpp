#pragma once

//defines a AST node types

#include <DTK_PPC_Lexer/Lexer.hpp>

namespace PPC::Frontend::DTK
{
	//defines a AST node type
	enum class ASTNodeType
	{


		Count
	};

	//defines dot derective node metadata

	//defines register node metadata

	//defines a constant node metadata

	//defines a variable node metadata

	//defines a struct node metadata

	//defines a ASM instruction node metadata

	//defines a jump label node metadata

	//defines a function node metadata

	//defines a AST node
	struct ASTNode
	{
		ASTNodeType type = ASTNodeType::Count;
	};

	//generates AST tree
	std::vector<ASTNode> GenerateAST(const std::vector<Token>& tokens);
	
}