/*
Power PC transcompiler || created by Sean Mott 2024+

Allows a Game Cube/Wii ROM to be converted to C++
*/



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

	//lexes assembly into tokens
	PPC::Data::TranslationUnit tu; 
	//tu.LoadCode("C:/Decomps/TOD-Decomp/RawASM/asm/__init_cpp_exceptions.s");
	tu.LoadCode("C:/Decomps/TOD-Decomp/RawASM/asm/auto_00_80003100_init.s");
	std::vector<PPC::Stage1::Token> tokens = PPC::Stage1::LexTokens(tu);
	for (size_t i = 0; i < tokens.size(); ++i)
		tokens[i].Print();

	//output the C code

	getchar();
	return 0;
}