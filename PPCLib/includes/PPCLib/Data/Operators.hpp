#pragma once

//defines a operator token

#include <string>

//list all operator tokens
#define PPC_LEXER_OPERATOR_COUNT 6
static const char PPC_LEXER_OPERATOR_TOKEN_STRINGS[PPC_LEXER_OPERATOR_COUNT] = { ',', '(', ')', ':', '@', '+' };

//checks if it's a operator
static inline bool Subpass1_IsOperator(const char op)
{
	for (size_t i = 0; i < PPC_LEXER_OPERATOR_COUNT; ++i)
	{
		if (op == PPC_LEXER_OPERATOR_TOKEN_STRINGS[i])
			return true;
	}

	return false;
}