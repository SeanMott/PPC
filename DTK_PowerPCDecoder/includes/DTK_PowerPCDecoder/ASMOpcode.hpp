#pragma once

//defines a Power PC Opcode

#include <DTK_PowerPCDecoder/AssemblyInstructions.hpp>

namespace PPC::Decoder::ASM
{
	//defines a opcode
	struct Opcode
	{
		//instruction
		Decoder::ASM::EInstruction instruction = Decoder::ASM::EInstruction::eInstruction_nop; //instruction
		Decoder::ASM::ASMInstructionKind kind = Decoder::ASM::ASMInstructionKind::Max; //specific kind of instruction
		std::string instructionStr = ""; //the instruction str

		//parameters
	};
}