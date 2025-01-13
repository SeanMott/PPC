#pragma once

//defines a condition register

#include <string>

//lists the condition registers
#define PPC_LEXER_CONDITION_REGISTER_COUNT 32
static const char* PPC_LEXER_CONDITION_REGISTER_STRINGS[PPC_LEXER_CONDITION_REGISTER_COUNT] = {
	"cr0lt",
	"cr0gt",
	"cr0eq",
	"cr0un",
	"cr1lt",
	"cr1gt",
	"cr1eq",
	"cr1un",
	"cr2lt",
	"cr2gt",
	"cr2eq",
	"cr2un",
	"cr3lt",
	"cr3gt",
	"cr3eq",
	"cr3un",
	"cr4lt",
	"cr4gt",
	"cr4eq",
	"cr4un",
	"cr5lt",
	"cr5gt",
	"cr5eq",
	"cr5un",
	"cr6lt",
	"cr6gt",
	"cr6eq",
	"cr6un",
	"cr7lt",
	"cr7gt",
	"cr7eq",
	"cr7un"
};

//checks if it's a condition register
static inline bool Subpass2_IsConditionRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_CONDITION_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_CONDITION_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}