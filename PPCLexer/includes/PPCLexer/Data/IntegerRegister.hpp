#pragma once

//defines a integer register

//lists the integer registers
#define PPC_LEXER_INTEGER_REGISTER_COUNT 32
static const char* PPC_LEXER_INTEGER_REGISTER_STRINGS[PPC_LEXER_INTEGER_REGISTER_COUNT] = {
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19",
	"r20", "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"
};

//checks if it's a integer register
static inline bool Subpass2_IsIntegerRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_INTEGER_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_INTEGER_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}
