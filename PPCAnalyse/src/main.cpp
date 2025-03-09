/*
Splits a ROM and generates the needed extra data for static recomping
*/

#include <PPCAnalyse/Arguments/ArgumentParser.hpp>

#include <PPCAnalyse/SymbolMap/Stage_DTKSymbolsToPPCMap.hpp>

#include <PPCAnalyse/ASM/Stage1/Stage1ASM.hpp>
#include <PPCAnalyse/ASM/Stage1/Stage1_ExtractDefinitions.hpp>
#include <PPCAnalyse/ASM/Stage1/Stage1_StripStructComments.hpp>
#include <PPCAnalyse/ASM/Stage1/Stage1_Subpass1_StringsAndOperators.hpp>

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

	const std::filesystem::path recompDir_CppCode = "C:/Decomps/GameCube/TODDecomp/Recomp/Cpp";

	//extracts ROM

	//generates DTK config

	//split into ASM

	//convert DTK symbol list into PPC Map
	//PPC::Analyse::Stage::Stage_DTKSymbolListToPPCMap(settings.DTK_splitsNSymbolsDir, settings.PPC_symbolMapDir, settings.generateTypeNames, settings.isPretty);
	//std::vector<PPC::SymbolMap::PPCSymbol> symbols = PPC::SymbolMap::LoadPPCSymbolMap(
	//	std::filesystem::path(settings.PPC_symbolMapDir.string() + "/Map" + PPC_MAP_FILE_EXTENSION));
	//const size_t symbolCount = symbols.size();
	
	//scan the types and rename the structs and remove any annoying names with strings

	//regen the assembly

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

			//purns everything that isn't a function, struct, or sym define
			std::vector<std::string> funcBodyStrs, structBodyStrs, funcPrototypeStrs, structPrototypeStrs;
			PPC::Analyse::ASM::Stage1::ExtractDefinitions(code, funcPrototypeStrs, funcBodyStrs, structPrototypeStrs, structBodyStrs);
			PPC::Analyse::ASM::Stage1::StripUnneededComments(structBodyStrs);

			//lexes the file into a token stream
			
			//generate symbol IDs

			//emits C++
			for (size_t i = 0; i < funcBodyStrs.size(); ++i)
			{
				//generate the prototype
				const std::vector<std::string> words = PPC::Analyse::ASM::Stage1::SplitLineIntoWords(funcPrototypeStrs[i]);
				std::string identifier = words[1]; identifier.resize(identifier.size() - 1);
				const std::string prototype = "void " + identifier + "(PPC::Runtime::GCContext* context)";

				//generates the body
				std::string body = "\n{\n" + funcBodyStrs[i] + "\n}";

				//stitches it togeather
				const std::string cppCode = prototype + body;

				std::string filepath = recompDir_CppCode.string() + "/" + identifier + ".cpp";
				std::ofstream cGen(filepath);
				cGen.write(cppCode.c_str(), cppCode.size());
			}

			for (size_t i = 0; i < structBodyStrs.size(); ++i)
			{
				//generate the prototype
				const std::vector<std::string> words = PPC::Analyse::ASM::Stage1::SplitLineIntoWords(structPrototypeStrs[i]);
				std::string identifier = words[1]; identifier.resize(identifier.size() - 1);
				const std::string prototype = "struct " + identifier;

				//generates the body
				std::string body = "\n{\n" + structBodyStrs[i] + "\n}";

				//stitches it togeather
				const std::string cppCode = prototype + body;

				std::string filepath = recompDir_CppCode.string() + "/" + identifier + ".hpp";
				std::ofstream cGen(filepath);
				cGen.write(cppCode.c_str(), cppCode.size());
			}

		}
	}

	//getchar();
	return 0;
}