#pragma once

//defines the floating registers

#include <string>

//lists the floating registers
#define PPC_LEXER_FLOATING_REGISTER_COUNT 32
static const char* PPC_LEXER_FLOATING_REGISTER_STRINGS[PPC_LEXER_FLOATING_REGISTER_COUNT] = {
	"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19",
	"f20", "f21", "f22", "f23", "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31"
};

//checks if it's a floating register
static inline bool Subpass2_IsFloatingRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_FLOATING_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_FLOATING_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}