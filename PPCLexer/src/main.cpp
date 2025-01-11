/*
PPC Lexer that converts DTK Raw Assembly into a stream of tokens
*/

#include <filesystem>

#include <PPCLexer/Subpasses/Subpass1.hpp>

//loads the translation unit code
static inline void LoadASM(const std::filesystem::path& filepath, std::string& code)
{
	FILE* file = fopen(filepath.string().c_str(), "r");
	fseek(file, 0, SEEK_END);
	const size_t codeLength = ftell(file);
	fseek(file, 0, SEEK_SET);
	code.resize(codeLength);
	fread(code.data(), sizeof(char), codeLength, file);
	fclose(file);
}

//entry point
int main()
{
	//loads the code
	const std::string ASMDirectory = "C:/Decomps/TOD-Decomp/RawASM/asm/";
	std::vector<std::string> ASMFiles; ASMFiles.reserve(5);
	for (const auto& entry : std::filesystem::directory_iterator(ASMDirectory))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".s") {
			ASMFiles.emplace_back(entry.path().string());
		}
	}
	//const std::string ASMFileName = "auto_00_80003100_init";
	//const std::string ASMFileName = "auto_05_80047290_data";
	//const std::string ASMFileName = "__init_cpp_exceptions";
	//const std::string ASMFileName = "auto_01_800056A0_text";
	for (size_t i = 0; i < ASMFiles.size(); ++i)
	{
		std::string code = "";
		LoadASM(ASMFiles[i], code);
	
		//runs the first pass || generates general tokens, comments, operators, and string literals
	 	std::vector<PPC::Stage1::Token> tokens = PPC::Stage1::Subpass1_GenerateGeneralTokens(code);

		//runs the second pass || strips invalide and illegal tokens and optionally all comments

		//runs the second pass || gives every token fine typing

		fmt::print("File: {}\n\n\n", ASMFiles[i]);
		for (size_t t = 0; t < tokens.size(); ++t)
			tokens[t].Print();
	}

	getchar();
	return 0;
}