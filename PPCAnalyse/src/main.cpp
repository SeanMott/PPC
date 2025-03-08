/*
Splits a ROM and generates the needed extra data for static recomping
*/

#include <PPCAnalyse/Arguments/ArgumentParser.hpp>

#include <PPCAnalyse/SymbolMap/Stage_DTKSymbolsToPPCMap.hpp>

#include <PPCAnalyse/ASM/Stage1/Stage1ASM.hpp>
#include <PPCAnalyse/ASM/Stage1/Stage1_ExtractDefinitions.hpp>
#include <PPCAnalyse/ASM/Stage1/Stage1_Subpass1_StringsAndOperators.hpp>

//lexes a block of code into a series of tokens

//defines a function definition
struct FunctionDef
{
	//prototype
	PPC::Data::Scope::ScopeType scope = PPC::Data::Scope::ScopeType::Count;
	std::string name = "";

	//body
};

//defines a struct definition
struct StructDef
{
	//prototype
	PPC::Data::Scope::ScopeType scope = PPC::Data::Scope::ScopeType::Count;
	std::string name = "";

	//body
};

//defines a sym definition

//entry point
int main(int args, const char* argv[])
{
	//parses arguments
	PPC::Analyse::Arguments::ArgumentSettings settings = PPC::Analyse::Arguments::ParseArguments(args, argv);

	//temp set
	settings.DTK_asmDir = "C:/Decomps/GameCube/TODDecomp/RawASM/asm";
	settings.DTK_splitsNSymbolsDir = "C:/Decomps/GameCube/TODDecomp/RawASM/DTKSymbolsNSplits";
	settings.PPC_symbolMapDir = "C:/Decomps/GameCube/TODDecomp/Recomped/SymbolMaps";
	settings.PPC_tokenizedASMFilesDir = "C:/Decomps/GameCube/TODDecomp/Recomped/TokenizedASM";
	settings.generateTypeNames = true;
	settings.splitIntoOwnFiles = true;

	//extracts ROM

	//generates DTK config

	//split into ASM

	//convert DTK symbol list into PPC Map
	//PPC::Analyse::Stage::Stage_DTKSymbolListToPPCMap(settings.DTK_splitsNSymbolsDir, settings.PPC_symbolMapDir, settings.generateTypeNames, settings.isPretty);
	//std::vector<PPC::SymbolMap::PPCSymbol> symbols = PPC::SymbolMap::LoadPPCSymbolMap(
	//	std::filesystem::path(settings.PPC_symbolMapDir.string() + "/Map" + PPC_MAP_FILE_EXTENSION));
	//const size_t symbolCount = symbols.size();
	
	//goes through the asm and perform lexing
	for (const auto& entry : std::filesystem::directory_iterator(settings.DTK_asmDir))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".s")
		{
			//loads file
			FILE* file = fopen(entry.path().string().c_str(), "r");
			fseek(file, 0, SEEK_END);
			const size_t codeLength = ftell(file);
			fseek(file, 0, SEEK_SET);
			std::string code; code.resize(codeLength);
			fread(code.data(), sizeof(char), codeLength, file);
			fclose(file);

			//splits the inital file into strings and finds all the structs, functions, and sym definitions
			std::vector<std::string> defStrings = PPC::Analyse::ASM::Stage1::ExtractDefinitions(code);

			//parses the defs into their own token streams
			for (size_t i = 0; i < defStrings.size(); ++i)
			{
				//generate the intial token stream
				std::vector<PPC::Token::Token> tokens = PPC::Analyse::ASM::Stage1::Subpass::PerformSubpass1(defStrings[i]);

				//extract the prototype
				//0 = def start keyword ".obj", ".fn", or ".sym"
				//1 = name
				//2 = comma
				//3 = scope type
				//4 = new line
				fmt::print("{}, {}\n", tokens[1].data, tokens[3].data);

				//extract the closing statment
				//tokens.size() - 2 = def end keyword ".endobj" or ".endfn"
				//tokens.size() - 1 = name
			}

			//emits C++
			for (size_t i = 0; i < defStrings.size(); ++i)
			{
				const std::string code = defStrings[i];

				//writes to disc
				std::string filepath = settings.PPC_tokenizedASMFilesDir.string() + "/" + std::to_string(i) + ".cpp";
				std::ofstream cGen(filepath);
				cGen.write(code.c_str(), code.size());
			}
		}
	}

	////function and struct prototypes
	//std::vector<FunctionDefintion> functionDefinitions; functionDefinitions.reserve(10);
	//std::vector<StructDefinition> structDefinitions; structDefinitions.reserve(10);

	////limited scope for string parsing for prototypes
	//{

	////splits code amd remove excess shit 
	//std::vector<std::string> funcPrototypesStrs, structPrototypesStrs;
	//std::vector<std::vector<std::string>> funcBodiesStrs, structBodiesStrs;
	//funcPrototypesStrs.reserve(10); funcBodiesStrs.reserve(10); structPrototypesStrs.reserve(10); structBodiesStrs.reserve(10);
	//SplitNStripASMIntoFuncsStructsAndSyms(settings.DTK_asmDir,
	//	funcPrototypesStrs, funcBodiesStrs, structPrototypesStrs, structBodiesStrs);

	////generate function and struct prototypes
	//for (size_t i = 0; i < funcBodiesStrs.size(); ++i)
	//{
	//	FunctionDefintion def;

	//	std::vector<std::string> words = SplitLineIntoWords(funcPrototypesStrs[i]);

	//	//0 = fn start asm macro
	//	//1 = name of the function, has a comma at the end of it at this point
	//	//2 = is it a weak, global, or local function

	//	//gets the name of the function and strips the comma after it
	//	def.identifierName = words[1]; def.identifierName.resize(words.size() - 1);

	//	//gets the scope
	//	def.scopeType = PPC::Data::Scope::ConvertDTKKeywordStringToScopeType(words[2]);

	//	//parses the body into 

	//	//store rest of the body
	//	def.bodyStrs = funcBodiesStrs[i];
	//}
	//for (size_t i = 0; i < structBodiesStrs.size(); ++i)
	//{
	//	StructDefinition def;

	//	std::vector<std::string> words = SplitLineIntoWords(structPrototypesStrs[i]);

	//	//0 = obj start asm macro
	//	//1 = name of the struct, has a comma at the end of it at this point
	//	//2 = is it a weak, global, or local structtion

	//	//gets the name of the structtion and strips the comma after it
	//	def.identifierName = words[1]; def.identifierName.resize(words.size() - 1);

	//	//gets the scope
	//	def.scopeType = PPC::Data::Scope::ConvertDTKKeywordStringToScopeType(words[2]);

	//	//store rest of the body
	//	def.bodyStrs = structBodiesStrs[i];
	//}
	//}

	////parses each line into tokens

	////autogenned C++
	//const std::string autoGenedCpp = "//this code is auto-genned by the PPC Toolchain.\n//Github: \"https://github.com/SeanMott/PPC\"\n\n"
	//	"//auto-included\n#include <PPCRuntime/Instructions.hpp>\n#include <PPCRuntime/GCContext.hpp>\n\n"
	//	"//genned from this project\n#include <PPCProject/Functions.hpp>\n#include <PPCProject/Structs.hpp>\n\n";

	////generate the giga function and struct headers, filled with the prototypes


	////emit C++ of the function token stream
	//for (size_t i = 0; i < functionDefinitions.size(); ++i)
	//{
	//	std::string filepath = settings.PPC_tokenizedASMFilesDir.string() + "/" + functionDefinitions[i].identifierName + ".cpp";
	//	std::string code = autoGenedCpp + "void " + functionDefinitions[i].identifierName + "(PPC::Runtime::GCContext* context)\n{\n";

	//	//emit C++ of tokens
	//	for (size_t t = 0; t < functionDefinitions[i].bodyStrs.size(); ++t)
	//		code += functionDefinitions[i].bodyStrs[t] + "\n";
	//	code += "}";

	//	std::ofstream cGen(filepath);
	//	cGen.write(code.c_str(), code.size());
	//}

	////emit C++ of the struct token stream
	//for (size_t i = 0; i < structDefinitions.size(); ++i)
	//{
	//	std::string filepath = settings.PPC_tokenizedASMFilesDir.string() + "/" + structDefinitions[i].identifierName + ".hpp";
	//	std::string code = autoGenedCpp + "struct " + structDefinitions[i].identifierName + "\n{\n";
	//	
	//	//emit C++ of tokens
	//	for (size_t t = 0; t < structDefinitions[i].bodyStrs.size(); ++t)
	//		code += structDefinitions[i].bodyStrs[t] + "\n";
	//	code += "};";

	//	std::ofstream cGen(filepath);
	//	cGen.write(code.c_str(), code.size());
	//}

	getchar();
	return 0;
}