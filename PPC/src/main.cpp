/*
PPC - Power PC To C Compiler

WIP Transcompiler for converting Game Cube Assembly to C++

*/

#include <string>
#include <filesystem>
#include <process.h>
#include <fstream>
#include <iostream>

#include <DTK_PPC_Lexer/Lexer.hpp>
#include <DTK_PPC_Lexer/AST.hpp>
#include <DTK_PPC_Lexer/Symbol.hpp>

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

//prints the version of the PPC
static inline void PrintVer()
{
	fmt::print(fmt::fg(fmt::color::deep_sky_blue), "Power PC To C Compiler (PPC) ");
	fmt::print("Ver: ");
	fmt::print(fmt::fg(fmt::color::crimson), "0.2.1");
	fmt::print(" || ");
	fmt::print(fmt::fg(fmt::color::dark_violet), "Apocrypha-Beta\n\n");
}

//if no arguments are passed
static inline void Help()
{
	//prints version information
	PrintVer();

	//stage 0 || decompiles a ROM and extracts all the symbol and ASM

	//stage 1 || inital ASM and symbol analisys and generates lex caches to use in other stages
}

//renames all structs based on type
static inline void ActionFlag_RenameStructsBasedOnType()
{
	//gets all the files and lexes them, store in temporary cache

	//turn lexed files into ASTs

	//parse current symbols

	//generate names for stucts based on type

	//copy symbol list and change names

	//run symbol patcher and update names in the lex cache then write back to file

	//delete temp cache of lexed data
}

//entry point
int main(int args, const char* argv)
{
	//--arg

	//--set flag for generating sudo-C human readable code
	//this assembly is just a cleaned up version of with less of the extra syntax needed for compiling ASM
	//if also provides type information

	//Help();

	const std::string ASMDir = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm";
	//const std::string ASMDir = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm";
	//const std::string ASMFile = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm/__init_cpp_exceptions.s";
	//const std::string ASMFile = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm/auto_11_805DE700_sdata2.s";
	//const std::string ASMFile = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA/asm/auto_11_805DE700_sdata2.s";

	const std::string ASMFile = "C:/Decomps/TOD/asm/auto_09_8004FDA0_sdata2.s";
	const std::string symbolFile = "C:/Decomps/TOD/symbols.txt";

	//loads the symbol data
	//std::vector<PPC::Frontend::Symbol::Symbol> symbols = PPC::Frontend::Symbol::ParseSymbolFile(symbolFile);
	std::vector<PPC::Frontend::DTK::Symbol::Symbol> symbols; symbols.reserve(200);
	std::ifstream input(symbolFile);
	for (std::string line; getline(input, line); )
	{
		PPC::Frontend::DTK::Symbol::Symbol symbol;
		//splits line
		const size_t lineCount = line.size();
		std::vector<std::string> parts; parts.reserve(5);
		std::string data = "";
		for (size_t i = 0; i < lineCount; ++i)
		{
			if (line[i] == ' ' || line[i] == '\n')
			{
				parts.emplace_back(data);
				data = "";
				continue;
			}

			data += line[i];
		}

		//gets the name, always 0
		symbol.name = parts[0];

		//searches for the type
		for (uint32_t i = 4; i < parts.size(); ++i)
		{
			if (!strcmp("type:object", parts[i].c_str()))
			{
				symbol.type = PPC::Frontend::DTK::Symbol::SymbolType::Object;
				break;
			}
			else if (!strcmp("type:function", parts[i].c_str()))
			{
				symbol.type = PPC::Frontend::DTK::Symbol::SymbolType::Function;
				break;
			}
			else if (!strcmp("type:label", parts[i].c_str()))
			{
				symbol.type = PPC::Frontend::DTK::Symbol::SymbolType::Label;
				break;
			}

			fmt::print("part {}: {} || ", i, parts[i]);
			fmt::print("\n");
		}

		symbols.emplace_back(symbol);
	}

	//reads the ASM code
	std::ifstream t(ASMFile);
	t.seekg(0, std::ios::end);
	size_t size = t.tellg();
	std::string buffer(size, '\0');
	t.seekg(0);
	t.read(&buffer[0], size);
	t.close();

	//lexes
	//std::string output = "";
	std::vector<PPC::Frontend::DTK::Token> tokens = PPC::Frontend::DTK::ASMParser(buffer);
	//for (size_t t = 0; t < tokens.size(); ++t)
		//output += tokens[t].Print();

	//gets file name

	//writes lex cache

	//generate AST
	std::vector<PPC::Frontend::DTK::ASTNode> tree = PPC::Frontend::DTK::GenerateAST(tokens, symbols);
	for (size_t t = 0; t < tree.size(); ++t)
	{
		tree[t].Print();

		// std::string data = ""
		//fmt::print("struct {} {\n",tree[t].structMetadata.structName.c_str());

		//fmt::print("};\n");
	}

	//generate Translation Unit

	//perform stage 0
	//Stage_Zero(ROMPath, projectPath);

	//perform stage 1

	//--clean up

	getchar();
	return 0;
}