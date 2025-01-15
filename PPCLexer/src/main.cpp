/*
PPC Lexer that converts DTK Raw Assembly into a stream of tokens
*/

#include <filesystem>

#include <PPCLexer/Subpasses/Subpass1.hpp>
#include <PPCLexer/Subpasses/Subpass2.hpp>
#include <PPCLexer/Subpasses/SubpassExtraStripping.hpp>

#include <PPCLexer/LexedFile.hpp>

#include <PPCLib/SymbolMap/PPCSymbol.hpp>

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
static inline void GeneratePureDTKTokenStream(const std::filesystem::path& ASMFile, std::vector<PPC::Stage1::Token>& tokenStream,
	const std::vector<PPC::SymbolMap::PPCSymbol>& symbols)
{
	std::string code = "";
	LoadASM(ASMFile.string(), code);

	//runs the first pass || generates general tokens, comments, operators, and string literals
	tokenStream = PPC::Stage1::Subpass1_GenerateGeneralTokens(code);

	//fine types the registers, instructions, memory offsets, scoping, pre-defined keywords
	//and datatypes
	tokenStream = PPC::Lexer::Subpass::Subpass2_GenerateFineTyping(tokenStream);

	//replaces all symbol identifiers with symbol IDs
	const size_t symbolCount = symbols.size();
	for (size_t i = 0; i < tokenStream.size(); ++i)
	{
		//checks if it's a symbol
		if (tokenStream[i].type == PPC::Stage1::TokenType::Identifier || tokenStream[i].type == PPC::Stage1::TokenType::Literal_String)
		{
			for (size_t s = 0; s < symbolCount; ++s)
			{
				if (symbols[s].identifier == tokenStream[i].data)
				{
					tokenStream[i].symbolID = s;
					tokenStream[i].type = PPC::Stage1::TokenType::Symbol_ID;
				}
			}
		}
	}
}

//gets every assembly file in a directory
static inline std::vector<std::filesystem::path> GetAllASMFilesInDirectory(const std::filesystem::path& dir)
{
	const std::string ASMDirectory = dir.string();
	std::vector<std::filesystem::path> files; files.reserve(5);
	for (const auto& entry : std::filesystem::directory_iterator(ASMDirectory))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".s")
			files.emplace_back(entry);
	}
	return files;
}

//parses a assembly file into a PPC Token
static std::vector<PPC::Stage1::Token> ParseDTKAssemblyIntoTokenStream(const std::filesystem::path& file, const std::vector<PPC::SymbolMap::PPCSymbol>& symbols,
	const std::filesystem::path& PPCTokenStreamOutputDir)
{
	const std::string filename = file.stem().string();

	//we always generate a Pure DTK Token Stream before we start making changes that won't let us have normal files
	std::vector<PPC::Stage1::Token> tokens;
	GeneratePureDTKTokenStream(file, tokens, symbols);

	//strips and invalid tokens
	tokens = PPC::Lexer::Subpass::ExtraSubpass_RemoveInvalidInstructions(tokens);

	//strips sector content and comments
	tokens = PPC::Lexer::Subpass::ExtraSubpass_StripCommentsAndSectors(tokens);

	//dumps the token stream of raw DTK ASM
	PPC::Stage1::DumpTokenStream(PPCTokenStreamOutputDir.string() + "/" + filename + ".ppctokens", tokens);
}

//gets every token stream file in a directory
static inline std::vector<std::filesystem::path> GetAllPPCTokenFilesInDirectory(const std::filesystem::path& dir)
{
	const std::string ASMDirectory = dir.string();
	std::vector<std::filesystem::path> files; files.reserve(5);
	for (const auto& entry : std::filesystem::directory_iterator(ASMDirectory))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".ppctokens")
			files.emplace_back(entry);
	}
	return files;
}

//entry point
int main()
{
	//loads the symbol files
	std::vector<PPC::SymbolMap::PPCSymbol> symbols = PPC::SymbolMap::LoadPPCSymbolMap("C:/Decomps/TOD-Decomp/RawASM/DTKSymbolsNSplits/PureDTKSymbols.ppcmap");

	//gets the PPC Token files
	const std::vector<std::filesystem::path> files = GetAllPPCTokenFilesInDirectory("C:/Decomps/TOD-Decomp/TypedASM/asm");


	getchar();
	return 0;
}