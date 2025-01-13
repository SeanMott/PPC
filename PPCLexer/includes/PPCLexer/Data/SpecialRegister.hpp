#pragma once

//defines if a string is a special register

#include <string>

//lists the special registers
#define PPC_LEXER_SPECIAL_REGISTER_COUNT 68
static const char* PPC_LEXER_SPECIAL_REGISTER_STRINGS[PPC_LEXER_SPECIAL_REGISTER_COUNT] = {
	"XER", 
"LR",
"CTR",
"DSISR",
"DAR",
"DEC",
"SDR1",
"SRR0",
"SRR1",
"SPRG0",
"SPRG1",
"SPRG2",
"SPRG3",
"EAR",
"PVR",
"IBAT0U",
"IBAT0L",
"IBAT1U",
"IBAT1L",
"IBAT2U",
"IBAT2L",
"IBAT3U",
"IBAT3L",
"DBAT0U",
"DBAT0L",
"DBAT1U",
"DBAT1L",
"DBAT2U",
"DBAT2L",
"DBAT3U",
"DBAT3L",
"GQR0",
"GQR1",
"GQR2",
"GQR3",
"GQR4",
"GQR5",
"GQR6",
"GQR7",
"HID2",
"WPAR",
"DMA_U",
"DMA_L",
"UMMCR0",
"UPMC1",
"UPMC2",
"USIA",
"UMMCR1",
"UPMC3",
"UPMC4",
"USDA",
"MMCR0",
"PMC1",
"PMC2",
"SIA",
"MMCR1",
"PMC3",
"PMC4",
"SDA",
"HID0",
"HID1",
"IABR",
"DABR",
"L2CR",
"ICTC",
"THRM1",
"THRM2",
"THRM3"
};

//checks if it's a special register
static inline bool Subpass2_IsSpecialRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_SPECIAL_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_SPECIAL_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}
