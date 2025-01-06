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
	//parse comments

	//loads the code
	PPC::Data::TranslationUnit tu;
	//tu.LoadCode("C:/Decomps/TOD-Decomp/RawASM/asm/__init_cpp_exceptions.s");
	tu.LoadCode("C:/Decomps/TOD-Decomp/RawASM/asm/auto_00_80003100_init.s");

	//lexes assembly into tokens	
	PPC::Stage1::LexedFile f = PPC::Stage1::LexTokens(tu.code);
	//for (size_t i = 0; i < f.funcs.size(); ++i)
	//{
	//	for (size_t t = 0; t < f.funcs[i].tokens.size(); ++t)
	//		f.funcs[i].tokens[t].Print();
	//}
	//for (size_t i = 0; i < f.structs.size(); ++i)
	//{
	//	for (size_t t = 0; t < f.structs[i].tokens.size(); ++t)
	//		f.structs[i].tokens[t].Print();
	//}
	for (size_t i = 0; i < f.wholeTokens.size(); ++i)
		f.wholeTokens[i].Print();

	//output the C code

	getchar();
	return 0;
}