/*
Converts split assembly into C++ code
*/

#include <PPCRecomp/Arguments/ArgumentParser.hpp>

#include <PPCLib/SymbolMap/PPCSymbol.hpp>
#include <PPCLib/Token/Token.hpp>

int main(int args, const char* argv[])
{
	//parse arguments
	PPC::Recomp::Arguments::ArgumentSettings settings = PPC::Recomp::Arguments::ParseArguments(args, argv);

	//temp set the variables
	settings.symbolMap = "C:/Decomps/GameCube/TODDecomp/Recomped/SymbolMaps/Map.ppcmap";
	settings.tokenizedASMDir = "C:/Decomps/GameCube/TODDecomp/Recomped/TokenizedASM";
	settings.codeOutputDir = "C:/Decomps/GameCube/TODDecomp/Recomped/OutputtedC";

	//load symbol map of typed info or regular map
	//std::vector<PPC::SymbolMap::PPCSymbol> symbols = PPC::SymbolMap::LoadPPCSymbolMap(settings.symbolMap);

	//stores the function, structs, and sym/label definitions
	std::vector<std::string> functionNames, structNames, sym_label_Names;
	functionNames.reserve(20); structNames.reserve(20); sym_label_Names.reserve(20);

	//load each Tokenized file
	for (const auto& entry : std::filesystem::directory_iterator(settings.tokenizedASMDir))
	{
		if (entry.is_regular_file() && entry.path().extension() == PPC_TOKEN_STREAM_FILE_EXTENSION)
		{
			//loads file
			const std::vector<PPC::Token::Token> tokens = PPC::Token::LoadTokenStream(entry.path());
			const size_t tokenCount = tokens.size();

			//goes through the tokens and gets the functions, structs, and sym/label defines
			std::vector<std::string> localFileFunctionNames, localFileStructNames, localFileSym_label_Names;
			localFileFunctionNames.reserve(20); localFileStructNames.reserve(20); localFileSym_label_Names.reserve(20);
			
			for (size_t t = 0; t < tokenCount; ++t)
			{
				//checks for func, struct, or sym/label defs
				if (tokens[t].type == PPC::Token::TokenType::Keyword_Object)
				{

					localFileStructNames.emplace_back(tokens[t + 1].data);

					////if struct
					////.obj __destroy_global_chain_reference, global
					////.endobj __destroy_global_chain_reference
					//if (tokens[t].objType == PPC::Data::ObjectType::ObjectType::Object_Start)
					//{
					//	//gets name
					//	t++;
					//	const std::string symbolName = tokens[t].data;
					//	structNames.emplace_back(symbolName);
					//	localFileStructNames.emplace_back(symbolName);
					//	fmt::print("Struct Found \"{}\"\n", symbolName);

					//	//skip comma and get scope keyword
					//	t += 2;
					//	//get scope data here

					//	//goes till the end of the struct
					//	t++;
					//	while (t < tokenCount && tokens[t].type != PPC::Stage1::TokenType::Keyword_Object && tokens[t].objType != PPC::Data::ObjectType::ObjectType::Object_End)
					//	{
					//		t++;
					//	}
					//}

					////if func
					////.fn __init_cpp_exceptions, global
					////.endfn __init_cpp_exceptions
					//else if (tokens[t].objType == PPC::Data::ObjectType::ObjectType::Func_Start)
					//{
					//	//gets name
					//	t++;
					//	const std::string symbolName = tokens[t].data;
					//	functionNames.emplace_back(symbolName);
					//	localFileFunctionNames.emplace_back(symbolName);
					//	fmt::print("Func Found \"{}\"\n", symbolName);

					//	//skip comma and get scope keyword
					//	t += 2;
					//	//get scope data here

					//	//goes till the end of the func
					//	t++;
					//	while (t < tokenCount && tokens[t].type != PPC::Stage1::TokenType::Keyword_Object && tokens[t].objType != PPC::Data::ObjectType::ObjectType::Func_End)
					//	{
					//		t++;
					//	}
					//}

					////if sym/label
					////.sym _savefpr_16, global
					//else if (tokens[t].objType == PPC::Data::ObjectType::ObjectType::Label_Sym)
					//{
					//	//gets name
					//	t++;
					//	const std::string symbolName = tokens[t].data;
					//	sym_label_Names.emplace_back(symbolName);
					//	localFileSym_label_Names.emplace_back(symbolName);
					//	fmt::print("Label Found \"{}\"\n", symbolName);

					//	//skip comma and get scope keyword
					//	t += 2;
					//	//get scope data here
					//}
				}
			}

			//generates the C++ code for this file
			std::string code = "//PPC Generated C++ Code, please verify manually.\n\n"
				"//the header files storing the generated prototypes for every func, struct, and sym/label defined in the cpp files.\n"
				"#include <PPCProject/Functions.hpp>\n#include <PPCProject/Structs.hpp>\n#include <PPCProject/Syms_Labels.hpp>\n\n";
			
			//generates the bodies of structs
			for (size_t s = 0; s < localFileStructNames.size(); ++s)
				code += "struct " + localFileStructNames[s] +"\n{\n\t//insert body definition here OwO\n};\n\n";

			//generates the bodies of functions
			for (size_t s = 0; s < localFileFunctionNames.size(); ++s)
				code += "void " + localFileFunctionNames[s] +"(PPC::Runtime::GCContext* context)\n{\n\t//insert body definition here OwO\n}\n\n";

			//write to disc
			std::ofstream f(settings.codeOutputDir.string() + "/" + entry.path().filename().stem().string() + ".cpp");
			f.write(code.c_str(), code.size());
			f.close();
		}
	}

	return 0;
}