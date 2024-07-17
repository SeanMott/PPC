/*
PPC - Power PC To C Compiler

WIP Transcompiler for converting Game Cube Assembly to C++

*/

#include <string>
#include <filesystem>
#include <process.h>
#include <fstream>

#include <DTK_PPC_Lexer/Lexer.hpp>

//calculates the position of what programs to use
const std::string workingDir = std::filesystem::current_path().string();

//change per platform
const std::string python = "C:/Compilers/PPC/tools/Windows_X64/Python_3.12.4/python.exe";

const std::string ninja = "C:/Compilers/PPC/tools/Windows_X64/ninja.exe";

const std::string dtk = "C:/Compilers/PPC/tools/Windows_X64/dtk.exe";

const std::string git = "C:/Compilers/PPC/tools/Windows_X64/Git/bin/git.exe";

//fixes a ROM
static inline void Tool_FixROM(const std::string& ROMPath, std::string outputROMPath)
{
	//fixes the ROM
	std::string pythonCommand = python + " Scripts/DTK_FixISO.py " + ROMPath + " " + outputROMPath;
	system(pythonCommand.c_str());
}

//performs stage 0
static inline void Stage_Zero(const std::string& ROMPath, const std::string& projectDir)
{
	//validate ROM

	//gets DTK
	std::string pythonCommand = python + " Scripts/GetDTK.py " + git + " " + projectDir;
	system(pythonCommand.c_str());

	//extract contents
	pythonCommand = python + " Scripts/DTK_ExtractROMContent.py " + dtk + " " + projectDir + " " + ROMPath;
	system(pythonCommand.c_str());

	//generate configs
	pythonCommand = python + " Scripts/DTK_GenerateConfig.py " + dtk + " " + projectDir;
	system(pythonCommand.c_str());

	//decompiles
	pythonCommand = python + " Scripts/DTK_Decompile.py " + python + " " + ninja + " " + projectDir;
	system(pythonCommand.c_str());

	//runs stage 0
	//std::string pythonCommand = python + " Scripts/Stage0.py " + python + " " + ninja + " " + dtk + " " + git + " " + projectDir + " " + ROMPath;
	//system(pythonCommand.c_str());
}

//performs stage 1
/*
The previously generated DTK ASM is parsed and tokenized.

This generates metadata on

1. File Aligment

2. Functions and struct names

3. Function code blocks and goto labels inside

4. struct definitions and variable types and values

*/
static inline void Stage_One()
{
	//consume Assembly

	//generate metadata
}

//if no arguments are passed
static inline void Help()
{
	
}

//entry point
int main(int args, const char* argv)
{
	//--arg

	const std::string ASMDir = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm";
	//const std::string ASMDir = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm";
	const std::string ASMFile = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm/__init_cpp_exceptions.s";

	//loads the symbol data

	//reads the ASM code
	FILE* file = nullptr;
	file = fopen(ASMFile.c_str(), "r");
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* text = (char*)calloc(length, length);
	if (text)
		fread(text, 1, length, file);
	fclose(file);

	//lexes
	PPC::Frontend::DTK::ASMParser(text);
	if(text)
		free(text);

	//perform stage 0
	//Stage_Zero(ROMPath, projectPath);

	//perform stage 1

	//--clean up

	getchar();
	return 0;
}