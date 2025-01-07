/*
Power PC transcompiler || created by Sean Mott 2024+

Allows a Game Cube/Wii ROM to be converted to C++
*/


#include <PPC/Data/TranslationUnit.hpp>
#include <PPC/Stage1/Token.hpp>

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
	PPC::Data::TranslationUnit tu;
	tu.SetASM("C:/Decomps/TOD-Decomp/RawASM/asm/auto_00_80003100_init.s");
	tu.SetASM("C:/Decomps/TOD-Decomp/RawASM/asm/auto_05_80047290_data.s");
	//tu.SetASM("C:/Decomps/TOD-Decomp/RawASM/asm/__init_cpp_exceptions.s");
	tu.LoadASM();

	//lexes assembly into tokens	
	PPC::Stage1::LexedFile f = PPC::Stage1::LexTokens(settings, tu.code);
	//for (size_t i = 0; i < f.wholeTokens.size(); ++i)
	//	f.wholeTokens[i].Print();
	//f.GenerateDebugOutputFileOfTokens("C:/Decomps/TOD-Decomp/RawASM/asm/TOD_DebugTokens_80003100_init.debugasm");
	//f.GenerateDebugOutputFileOfTokens("C:/Decomps/TOD-Decomp/RawASM/asm/TOD_DebugTokens_05_80047290_data.debugasm");

	//generates the IR as a translation unit
	//PPC::Stage2::TranslationUnit TU = PPC::Stage2::GenerateIR(settings, f);

	getchar();
	return 0;
}