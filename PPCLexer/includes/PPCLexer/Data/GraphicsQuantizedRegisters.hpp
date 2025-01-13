#pragma once

//defines if it's a graphics quantized register

#include <string>


//lists the graphics quantized registers
#define PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_COUNT 8
static const char* PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_STRINGS[PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_COUNT] = {
	"qr0", "qr1", "qr2", "qr3", "qr4", "qr5", "qr6", "qr7"
};

//checks if it's a graphics quantized register
static inline bool Subpass2_IsGraphicsQuantizedRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}
