#include <DTK_PPC_Lexer/AST.hpp>

std::vector<PPC::Frontend::DTK::ASTNode> PPC::Frontend::DTK::GenerateAST(const std::vector<PPC::Frontend::DTK::Token>& tokens)
{
	const size_t tokenCount = tokens.size();

	std::vector<PPC::Frontend::DTK::ASTNode> tree; tree.reserve(tokenCount / 2);

	for (size_t t = 0; t < tokenCount; ++t)
	{
		//checks dot directive
	}

	return tree;
}