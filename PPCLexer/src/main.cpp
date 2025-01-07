/*
Power PC transcompiler || created by Sean Mott 2024+

Allows a Game Cube/Wii ROM to be converted to C++
*/


#include <PPC/Data/ASMFile.hpp>

#include <PPC/Stage1/Token.hpp>
#include <PPC/Stage2/IR.hpp>

//the modes PPC can be in
enum class PPCMode
{
	Full = 0, //the default mode and will take the entire ROM and convert it to C++
	
	ASMType, //takes a ROM and generates the ASM then gives it type info but stays in ASM
};


//entry point
int main(int args, const char* argv[])
{
	//parse flags
	PPC::Data::CompilerSettings settings;
	settings.outputDebugASM = true;

	//loads the code
	PPC::Data::ASMFile ASMFile;
	//ASMFile.SetASM("C:/Decomps/TOD-Decomp/RawASM/asm/auto_00_80003100_init.s");
	//ASMFile.SetASM("C:/Decomps/TOD-Decomp/RawASM/asm/auto_05_80047290_data.s");
	//ASMFile.SetASM("C:/Decomps/TOD-Decomp/RawASM/asm/__init_cpp_exceptions.s");
	ASMFile.SetASM("C:/Decomps/TOD-Decomp/RawASM/asm/auto_01_800056A0_text.s");
	ASMFile.LoadASM();

	//lexes assembly into tokens	
	PPC::Stage1::LexedFile f = PPC::Stage1::LexTokens(settings, ASMFile.code);
	//for (size_t i = 0; i < f.wholeTokens.size(); ++i)
	//	f.wholeTokens[i].Print();
	//f.GenerateDebugOutputFileOfTokens("C:/Decomps/TOD-Decomp/RawASM/asm/TOD_DebugTokens_80003100_init.debugasm");
	//f.GenerateDebugOutputFileOfTokens("C:/Decomps/TOD-Decomp/RawASM/asm/TOD_DebugTokens_05_80047290_data.debugasm");

	//generates the IR as a translation unit
	std::vector<PPC::Stage2::Node> nodes = PPC::Stage2::ParseExpresstionsIntoNodeIR(f.singleLineExpesstions);
	std::string debugIR = "";
	for (size_t i = 0; i < nodes.size(); ++i)
		debugIR += nodes[i].GenerateDebugIR();

	//spits out a debug IR file
	//std::fstream debugIRFile("C:/Decomps/TOD-Decomp/RawASM/asm/00_80003100_init.sir", std::ios::out);
	//std::fstream debugIRFile("C:/Decomps/TOD-Decomp/RawASM/asm/05_80047290_data.sir", std::ios::out);
	std::fstream debugIRFile("C:/Decomps/TOD-Decomp/RawASM/asm/auto_01_800056A0_text.sir", std::ios::out);
	debugIRFile.write(debugIR.c_str(), debugIR.size());

	getchar();
	return 0;
}