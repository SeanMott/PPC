#pragma once

//defines registers used through out Power PC

#include <string>

namespace PPC::Decoder::Register
{
	//defines a general purpose register
	enum class IntegerGeneralPurposeRegister
	{
		r0 = 0,
		r1,
		r2,
		r3,
		r4,
		r5,
		r6,
		r7,
		r8,
		r9,
		r10,
		r11,
		r12,
		r13,
		r14,
		r15,
		r16,
		r17,
		r18, 
		r19,
		r20,
		r21,
		r22,
		r23,
		r24,
		r25,
		r26,
		r27,
		r28,
		r29,
		r30,
		r31,

		Max
	};

	static const char* GENERAL_INTEGER_REGISTER_KEYWORD_STR[(int)IntegerGeneralPurposeRegister::Max] = {
		"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",	
		
		"r10",	"r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19",	
		
		"r20",	"r21",	"r22",	"r23",	"r24",	"r25",	"r26",	"r27",	"r28",	"r29",	
		
		"r30",	"r31"
	};

	//checks if the string is a general purpose register
	inline bool IsString_GeneralIntegerRegister(const char* keyword, uint32_t& arrayIndex, IntegerGeneralPurposeRegister& registerEnum)
	{
		for (uint32_t i = 0; i < (int)IntegerGeneralPurposeRegister::Max; ++i)
		{
			if (!strcmp(keyword, GENERAL_INTEGER_REGISTER_KEYWORD_STR[i]))
			{
				arrayIndex = i;
				registerEnum = (IntegerGeneralPurposeRegister)i;
				return true;
			}
		}

		registerEnum = IntegerGeneralPurposeRegister::Max;
		return false;
	}

	//defines a floating point register
	enum class FloatingGeneralPurposeRegister
	{
		f0 = 0,
		f1,
		f2,
		f3,
		f4,
		f5,
		f6,
		f7,
		f8,
		f9,
		f10,
		f11,
		f12,
		f13,
		f14,
		f15,
		f16,
		f17,
		f18,
		f19,
		f20,
		f21,
		f22,
		f23,
		f24,
		f25,
		f26,
		f27,
		f28,
		f29,
		f30,
		f31,

		Max
	};

	static const char* GENERAL_FLOATING_REGISTER_KEYWORD_STR[(int)FloatingGeneralPurposeRegister::Max] = {
		"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9",

		"f10",	"f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19",

		"f20",	"f21",	"f22",	"f23",	"f24",	"f25",	"f26",	"f27",	"f28",	"f29",

		"f30",	"f31"
	};

	//checks if the string is a general purpose floating register
	inline bool IsString_GeneralFloatingRegister(const char* keyword, uint32_t& arrayIndex, FloatingGeneralPurposeRegister& registerEnum)
	{
		for (uint32_t i = 0; i < (int)IntegerGeneralPurposeRegister::Max; ++i)
		{
			if (!strcmp(keyword, GENERAL_FLOATING_REGISTER_KEYWORD_STR[i]))
			{
				arrayIndex = i;
				registerEnum = (FloatingGeneralPurposeRegister)i;
				return true;
			}
		}

		registerEnum = FloatingGeneralPurposeRegister::Max;
		return false;
	}

	//defines various registers as enums
	enum class Register_Keword_Enum
	{
		qr0, XER, GQR1, ICTC, cr0lt,
		qr1, LR, GQR2, THRM1, cr0gt,
		qr2, CTR, GQR3, THRM2, cr0eq,
		qr3, DSISR, GQR4, THRM3, cr0un,
		qr4, DAR, GQR5, cr1lt,
		qr5, DEC, GQR6, cr1gt,
		qr6, SDR1, GQR7, cr1eq,
		qr7, SRR0, HID2, cr1un,
		SRR1, WPAR, cr2lt,
		SPRG0, DMA_U, cr2gt,
		SPRG1, DMA_L, cr2eq,
		SPRG2, UMMCR0, cr2un,
		SPRG3, UPMC1, cr3lt,
		EAR, UPMC2, cr3gt,
		PVR, USIA, cr3eq,
		IBAT0U, UMMCR1, cr3un,
		IBAT0L, UPMC3, cr4lt,
		IBAT1U, UPMC4, cr4gt,
		IBAT1L, USDA, cr4eq,
		IBAT2U, MMCR0, cr4un,
		IBAT2L, PMC1, cr5lt,
		IBAT3U, PMC2, cr5gt,
		IBAT3L, SIA, cr5eq,
		DBAT0U, MMCR1, cr5un,
		DBAT0L, PMC3, cr6lt,
		DBAT1U, PMC4, cr6gt,
		DBAT1L, SDA, cr6eq,
		DBAT2U, HID0, cr6un,
		DBAT2L, HID1, cr7lt,
		DBAT3U, IABR, cr7gt,
		DBAT3L, DABR, cr7eq,
		GQR0, L2CR, cr7un,

		Count
	};

	//defines various registers
	static const char* REGISTER_KEYWORD_STR[(int)Register_Keword_Enum::Count] = {
			"qr0",	"XER",	"GQR1",	"ICTC",	"cr0lt",
			"qr1",	"LR",		"GQR2",	"THRM1","cr0gt",
			"qr2",	"CTR",	"GQR3",	"THRM2","cr0eq",
			"qr3",	"DSISR",	"GQR4",	"THRM3",	"cr0un",
			"qr4",	"DAR",	"GQR5",			"cr1lt",
			"qr5",	"DEC",	"GQR6",			"cr1gt",
			"qr6",	"SDR1",	"GQR7",			"cr1eq",
			"qr7",	"SRR0",	"HID2",			"cr1un",
					"SRR1", 	"WPAR",			"cr2lt",
					"SPRG0",	"DMA_U",			"cr2gt",
				"SPRG1",	"DMA_L",			"cr2eq",
				"SPRG2",	"UMMCR0",			"cr2un",
				"SPRG3",	"UPMC1",			"cr3lt",
				"EAR",	"UPMC2",			"cr3gt",
				"PVR",	"USIA", 			"cr3eq",
				"IBAT0U",	"UMMCR1",			"cr3un",
				"IBAT0L",	"UPMC3",			"cr4lt",
				"IBAT1U",	"UPMC4",			"cr4gt",
				"IBAT1L",	"USDA", 			"cr4eq",
				"IBAT2U",	"MMCR0",			"cr4un",
				"IBAT2L",	"PMC1", 			"cr5lt",
				"IBAT3U",	"PMC2",			"cr5gt",
				"IBAT3L",	"SIA", 			"cr5eq",
				"DBAT0U",	"MMCR1",			"cr5un",
				"DBAT0L",	"PMC3",			"cr6lt",
				"DBAT1U",	"PMC4",			"cr6gt",
				"DBAT1L",	"SDA", 			"cr6eq",
				"DBAT2U",	"HID0",			"cr6un",
				"DBAT2L",	"HID1",			"cr7lt",
				"DBAT3U",	"IABR",			"cr7gt",
				"DBAT3L",	"DABR",			"cr7eq",
				"GQR0",	"L2CR",			"cr7un",
	};

	//checks if the keyword is a register
	inline bool IsKeywordRegister(const char* keyword, uint32_t& arrayIndex, Register_Keword_Enum& registerEnum)
	{
		for (uint32_t i = 0; i < (int)Register_Keword_Enum::Count; ++i)
		{
			if (!strcmp(keyword, REGISTER_KEYWORD_STR[i]))
			{
				arrayIndex = i;
				registerEnum = (Register_Keword_Enum)i;
				return true;
			}
		}

		registerEnum = Register_Keword_Enum::Count;
		return false;
	}
}