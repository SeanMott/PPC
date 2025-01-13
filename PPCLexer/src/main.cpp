/*
PPC Lexer that converts DTK Raw Assembly into a stream of tokens
*/

#include <filesystem>

#include <PPCLexer/Subpasses/Subpass1.hpp>
#include <PPCLexer/Subpasses/Subpass2.hpp>
#include <PPCLexer/Subpasses/SubpassExtraStripping.hpp>

#include <PPCLexer/LexedFile.hpp>

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

//defines the mode of the lexer
enum class LexerMode
{
	PureDTK = 0, //this mode will reserve, every part of the DTK file parsed.
	//this is normally used if you are generating a PPC Token Stream for renaming or anaylizing a DTK project.
};

//generate a Pure DTK Token Stream
static inline void GeneratePureDTKTokenStream(const std::filesystem::path& ASMFile, std::vector<PPC::Stage1::Token>& tokenStream)
{
	std::string code = "";
	LoadASM(ASMFile.string(), code);

	//runs the first pass || generates general tokens, comments, operators, and string literals
	tokenStream = PPC::Stage1::Subpass1_GenerateGeneralTokens(code);

	//fine types the registers, instructions, memory offsets, scoping, pre-defined keywords
	//and datatypes
	tokenStream = PPC::Lexer::Subpass::Subpass2_GenerateFineTyping(tokenStream);
}

//entry point
int main()
{
	//gets the files
	const std::string ASMDirectory = "C:/Decomps/TOD-Decomp/RawASM/asm/";
	std::vector<PPC::Lexer::LexedFile> files; files.reserve(5);
	for (const auto& entry : std::filesystem::directory_iterator(ASMDirectory))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".s") 
		{
			PPC::Lexer::LexedFile f;
			f.ASMFile = entry.path();
			f.tokens.reserve(20);
			files.emplace_back(f);
		}
	}

	for (size_t i = 0; i < files.size(); ++i)
	{
		const std::string filename = files[i].ASMFile.stem().string();

		//we always generate a Pure DTK Token Stream before we start making changes that won't let us have normal files
		std::vector<PPC::Stage1::Token> tokens;
		GeneratePureDTKTokenStream(files[i].ASMFile, tokens);

		//strips and invalid tokens
		tokens = PPC::Lexer::Subpass::ExtraSubpass_RemoveInvalidInstructions(tokens);
		
		//strips sector content and comments
		tokens = PPC::Lexer::Subpass::ExtraSubpass_StripCommentsAndSectors(tokens);

		//splits every function and object defintion into their own subtrees

		//compress the tokens, generating the jump labels and alignment

		//generates the lexed file and gets the aligment

		//runs the second pass || gives every token fine typing

		//dump it all to a file
		//PPC::Lexer::DumpTokenStream(tokens, std::filesystem::path(std::string("C:/Decomps/TOD-Decomp/DTKTokenStream/") + filename + ".ppcTokenStream"));

		fmt::print("File: {}\n\n\n", files[i].ASMFile.string());
		for (size_t t = 0; t < tokens.size(); ++t)
			tokens[t].Print();
	}

	getchar();
	return 0;
}