/*
PPC - Power PC To C Compiler

WIP Transcompiler for converting Game Cube Assembly to C++

*/

#include <DTK_PPC_Lexer/Lexer.hpp>
#include <DTK_PPC_Lexer/AST.hpp>
#include <DTK_PPC_Lexer/Symbol.hpp>

#include <string>
#include <process.h>
#include <thread>

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


//defines a translation unit for conveting ASM to C++
struct TranslationUnit
{
	std::string filename = ""; //the name of the file

	std::string ASM = ""; //raw ASM code

	std::vector<std::string> structsUsedInThisFile; //the structs used in this file
	std::vector<std::string> functionsUsedInThisFile; //the functions used in this file
	std::vector<std::string> labelsUsedInThisFile; //the labels used in this file

	std::vector<std::string> structsDefinedInThisFile; //the structs defined in this file
	std::vector<std::string> functionsDefinedInThisFile; //the functions defined in this file
	std::vector<std::string> labelsDefinedInThisFile; //the labels defined in this file

	std::vector<PPC::Frontend::DTK::Token> tokens; //lexed tokens
	std::vector<PPC::Frontend::DTK::ASTNode> ASTTree; //AST tree
};

//generate AST info on another thread
void Thread_GenerateASTInfo(std::vector<TranslationUnit>& translationUnits, const std::vector<PPC::Frontend::DTK::Symbol::Symbol> symbols)
{
	for (size_t i = 0; i < translationUnits.size(); ++i)
	{
		translationUnits[i].tokens = PPC::Frontend::DTK::ASMParser(translationUnits[i].ASM);
		translationUnits[i].ASTTree = PPC::Frontend::DTK::GenerateAST(translationUnits[i].tokens, symbols);
	}
}

//renames symbols on another thread
void Thread_PatchSymbolsAndASMWithNewNames(std::vector<TranslationUnit>& translationUnits, 
	const std::vector<PPC::Frontend::DTK::Symbol::Symbol> oldSymbols, const std::vector<PPC::Frontend::DTK::Symbol::Symbol> patchedSymbols)
{
	const size_t symbolCount = oldSymbols.size();

	for (size_t i = 0; i < translationUnits.size(); ++i)
	{
		for (size_t t = 0; t < translationUnits[i].tokens.size(); ++t)
		{
			//check if matches a name that needs to be changed
			if (translationUnits[i].tokens[t].type == PPC::Frontend::DTK::TokenType::Identifier || translationUnits[i].tokens[t].type == PPC::Frontend::DTK::TokenType::Literal_String)
			{
				const char* d = translationUnits[i].tokens[t].data.c_str();

				for (size_t s = 0; s < symbolCount; ++s)
				{
					//skip if we aren't changing it
					if (!oldSymbols[s].hasBeenRenamed)
						continue;

					if (!strcmp(d, oldSymbols[s].name.c_str()))
					{
						fmt::print(fmt::fg(fmt::color::orchid), "Renamed {} to {}\n", translationUnits[i].tokens[t].data, patchedSymbols[s].name);
						translationUnits[i].tokens[t].data = patchedSymbols[s].name;
						break;
					}
				}
			}
		}
	}
}

//takes raw DTK assembly and outputs typedefed structs
static inline void RawDTKtoTypeDefedASM(const std::string& ASMDir, const std::string& symbolFile, const std::string& outputDir)
{
	//loads the symbol data
	std::vector<PPC::Frontend::DTK::Symbol::Symbol> symbols = PPC::Frontend::DTK::Symbol::GenerateSymbolsFrom_DTKSymbolFile(symbolFile);

	//threads
	const uint32_t maxThreadIndex = 6; uint32_t currentThreadIndex = 0;
	std::thread threads[maxThreadIndex]; bool threadDone[maxThreadIndex]; memset(threadDone, false, sizeof(bool) * maxThreadIndex);
	std::vector<TranslationUnit> translationUnits[maxThreadIndex];
	for (uint32_t i = 0; i < maxThreadIndex; ++i)
		translationUnits[i].reserve(10);

	//gets all the files in the ASM directory
	fmt::print(fmt::fg(fmt::color::cyan), "Gathering ASM files in ");
	fmt::print(fmt::fg(fmt::color::green), "\"{}\"\n", ASMDir);
	for (const auto& entry : std::filesystem::directory_iterator(ASMDir))
	{
		TranslationUnit unit; //makes a new translation unit

		//reads the ASM code and sorts into a thread
		std::ifstream t(entry.path());
		t.seekg(0, std::ios::end);
		size_t size = t.tellg();
		std::string buffer(size, '\0');
		t.seekg(0);
		t.read(&buffer[0], size);
		t.close();
		unit.ASM = buffer;

		//adds to pool
		translationUnits[currentThreadIndex].emplace_back(unit);

		//points to new thread
		currentThreadIndex++;
		if (currentThreadIndex >= maxThreadIndex)
			currentThreadIndex = 0;
	}

	//goes through all the files, loading, lexing and generating the AST
	fmt::print(fmt::fg(fmt::color::purple), "Generating Lexing Tokens and AST data....\n");
	for (uint32_t i = 0; i < maxThreadIndex; ++i)
		threads[i] = std::thread(Thread_GenerateASTInfo, std::ref(translationUnits[i]), symbols);

	//while the threads aren't done
	bool waitForThreads = true;
	uint32_t doneAccu = 0;
	while (waitForThreads)
	{
		for (uint32_t i = 0; i < maxThreadIndex; ++i)
		{
			if (!threadDone[i] && threads[i].joinable())
			{
				threads[i].join();
				threadDone[i] = true;
				doneAccu++;

				//fmt::print(fmt::fg(fmt::color::purple), "\n----DATA OF FILE----\n");
				//for (auto& unit : translationUnits[i])
				//{
				//	for (uint32_t n = 0; n < unit.ASTTree.size(); ++n)
				//		unit.ASTTree[n].Print();
				//}
			}
		}

		//check they are all done
		if (doneAccu >= maxThreadIndex)
			break;
	}

	fmt::print(fmt::fg(fmt::color::green), "Done Generating Lexing Tokens and AST data :3 \n");

	//regen the labels for renaming
	fmt::print(fmt::fg(fmt::color::purple), "Generating new struct names based on type info.....\n");
	std::vector<PPC::Frontend::DTK::Symbol::Symbol> newSymbols = symbols;
	const size_t symbolCount = newSymbols.size();
	size_t structTypeCurrentCount = 0,
		skipReserveAddressCurrentCount = 0,
		byteCurrentCount = 0, byte2CurrentCount = 0, byte4CurrentCount = 0,
		floatCurrentCount = 0, doubleCurrentCount = 0,
		funcPtrRefCurrentCount = 0, structRefCurrentCount = 0,
		stringCurrentCount = 0, asciiCurrentCount = 0;

	for (currentThreadIndex = 0; currentThreadIndex < maxThreadIndex; ++currentThreadIndex)
	{
		for (uint32_t i = 0; i < translationUnits[currentThreadIndex].size(); ++i)
		{
			for (uint32_t nodeIndex = 0; nodeIndex < translationUnits[currentThreadIndex][i].ASTTree.size(); ++nodeIndex)
			{
				PPC::Frontend::DTK::ASTNode* node = &(translationUnits[currentThreadIndex][i].ASTTree[nodeIndex]);

				//checks if it defines a struct
				if (node->type == PPC::Frontend::DTK::ASTNodeType::Struct)
				{
					//if it was in "" which is common for @, we want to remove thoses as they are annoying
					//or it starts with lbl_
					//theses are the structs we want to rename
					if (node->structMetadata.nameWasInAString ||
						node->structMetadata.structName.size() > 4 && node->structMetadata.structName[0] == 'l'
						&& node->structMetadata.structName[1] == 'b' && node->structMetadata.structName[2] == 'l' && node->structMetadata.structName[3] == '_')
					{
						//fmt::print("{}\n", node->structMetadata.structName);

						std::string newName = ""; bool newNameCouldBeGenerated = false;

						//add a extra check for "@etb_" and "@eti_" as we want to give them slightly differant names
						bool isETBSectorStruct = (node->structMetadata.structName.size() > 5 && node->structMetadata.structName[0] == '@'
							&& node->structMetadata.structName[1] == 'e' && node->structMetadata.structName[2] == 't' && node->structMetadata.structName[3] == 'b'
							&& node->structMetadata.structName[4] == '_');
						bool isETISectorStruct = (node->structMetadata.structName.size() > 5 && node->structMetadata.structName[0] == '@'
							&& node->structMetadata.structName[1] == 'e' && node->structMetadata.structName[2] == 't' && node->structMetadata.structName[3] == 'i'
							&& node->structMetadata.structName[4] == '_');

						if (isETISectorStruct)
							newName = "LBL_ETI_";
						else if (isETBSectorStruct)
							newName = "LBL_ETB_";
						else
							newName = "LBL_";

						//check what datatypes are inside
						PPC::Decoder::DotDirectives::DotDirective_Datatype datatype = PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte;
						if (node->structMetadata.variables.size() > 1)
						{
							datatype = node->structMetadata.variables[0].datatype; bool foundDiff = false;
							for (size_t v = 1; v < node->structMetadata.variables.size(); ++v)
							{
								if (node->structMetadata.variables[v].datatype != datatype)
								{
									foundDiff = true;
									break;
								}
							}
							newNameCouldBeGenerated = !foundDiff;
						}
						else
						{
							datatype = node->structMetadata.variables[0].datatype;
							newNameCouldBeGenerated = true;
						}

						//default name if we couldn't generate a specific one
						if (!newNameCouldBeGenerated)
						{
							newName += "STRUCT_" + std::to_string(structTypeCurrentCount);
							structTypeCurrentCount++;
						}
						//if we can generate one
						else
						{
							switch (datatype)
							{
							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte:
								newName += "BYTE_" + std::to_string(byteCurrentCount);
								byteCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte2:
								newName += "BYTE2_" + std::to_string(byte2CurrentCount);
								byte2CurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Skip_U16:
								newName += "SPACE_RESERVE_SKIP_" + std::to_string(skipReserveAddressCurrentCount);
								skipReserveAddressCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Float:
								newName += "FLOAT_" + std::to_string(floatCurrentCount);
								floatCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Double:
								newName += "DOUBLE_" + std::to_string(doubleCurrentCount);
								doubleCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::String:
								newName += "STRING_" + std::to_string(stringCurrentCount);
								stringCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Ascii:
								newName += "ASCII_" + std::to_string(asciiCurrentCount);
								asciiCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte4:
								newName += "BYTE4_" + std::to_string(byte4CurrentCount);
								byte4CurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte4_FunctionPtr:
								newName += "FUNCTION_PTR_" + std::to_string(funcPtrRefCurrentCount);
								funcPtrRefCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte4_Struct:
								newName += "STRUCT_REF_" + std::to_string(structRefCurrentCount);
								structRefCurrentCount++;
								break;

							case PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte4_Invalid:
								newName += "STRUCT_" + std::to_string(structTypeCurrentCount);
								structTypeCurrentCount++;
								break;

							default:
								newName += "STRUCT_" + std::to_string(structTypeCurrentCount);
								structTypeCurrentCount++;
								break;
							}
						}

						//updates the symbol
						const char* n = node->structMetadata.structName.c_str();
						for (size_t s = 0; s < symbolCount; ++s)
						{
							if (symbols[s].type != PPC::Frontend::DTK::Symbol::SymbolType::Object || symbols[s].hasBeenRenamed)
								continue;

							if (!strcmp(n, symbols[s].name.c_str()))
							{
								symbols[s].hasBeenRenamed = true;
								newSymbols[s].name = newName;
								break;
							}
						}
					}
				}
			}
		}
	}

	//goes through all the files, updating the struct instances
	currentThreadIndex = 0;
	memset(threadDone, false, sizeof(bool) * maxThreadIndex);
	waitForThreads = true;
	doneAccu = 0;
	for (uint32_t i = 0; i < maxThreadIndex; ++i)
		threads[i] = std::thread(Thread_PatchSymbolsAndASMWithNewNames, std::ref(translationUnits[i]), symbols, newSymbols);
	//for (uint32_t i = 0; i < maxThreadIndex; ++i)
		//Thread_PatchSymbolsAndASMWithNewNames(translationUnits[i], symbols, newSymbols);

	//while the threads aren't done
	while (waitForThreads)
	{
		for (uint32_t i = 0; i < maxThreadIndex; ++i)
		{
			if (!threadDone[i] && threads[i].joinable())
			{
				threads[i].join();
				threadDone[i] = true;
				doneAccu++;
				//fmt::print("Thread finished\n");

				//fmt::print(fmt::fg(fmt::color::purple), "\n----DATA OF FILE----\n");
				//for (auto& unit : translationUnits[i])
				//{
				//	for (uint32_t n = 0; n < unit.ASTTree.size(); ++n)
				//		unit.ASTTree[n].Print();
				//}
			}
		}

		//check they are all done
		if (doneAccu >= maxThreadIndex)
			break;
	}


	fmt::print(fmt::fg(fmt::color::green), "Finished generating new struct names, writng them to files at ");
	fmt::print(fmt::fg(fmt::color::cyan), "\"{}\"\n", outputDir);

	//writes symbol data
	std::string writeData = "";
	for (size_t s = 0; s < newSymbols.size(); ++s)
		writeData += newSymbols[s].FormatStringForPPCSymbolData();
	std::ofstream myfile;
	myfile.open(outputDir + "/symbols.ppcsym");
	myfile << writeData;
	myfile.close();
	writeData = "";

	//writes ASM
	std::filesystem::create_directory(outputDir + "/asm");
	for (uint32_t i = 0; i < maxThreadIndex; ++i)
	{
		for (size_t t = 0; t < translationUnits[i].size(); ++t)
		{
			//generate ASM
			writeData = "";
			for (size_t token = 0; token < translationUnits[i][t].tokens.size(); ++token)
				writeData += translationUnits[i][t].tokens[token].GenerateDTKAssembly();

			//write file
			std::ofstream myfile;
			myfile.open(outputDir + "/asm/" + translationUnits[i][t].tokens[4].data + ".s");
			myfile << writeData;
			myfile.close();
		}
	}
}

//entry point
int main(int args, const char* argv)
{
	//--arg

	//--set flag for generating sudo-C human readable code
	//this assembly is just a cleaned up version of with less of the extra syntax needed for compiling ASM
	//if also provides type information

	//Help();

	const std::string ASMDir = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA-Raw/asm";
	const std::string symbolFile = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA-Raw/symbols.tx";
	
	const std::string typedInfoDir = "C:/KARTools/PPC-KAR-HP-Decomp/BaseNA";
	
	RawDTKtoTypeDefedASM(ASMDir, symbolFile, typedInfoDir);

	//generates sudo


	//--clean up

	getchar();
	return 0;
}