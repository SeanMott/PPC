/*
PPC Lexer that converts DTK Raw Assembly into a stream of tokens
*/

#include <filesystem>

#include <PPCLexer/Subpasses/Subpass1.hpp>
#include <PPCLexer/Subpasses/Subpass2.hpp>
#include <PPCLexer/Subpasses/SubpassExtraStripping.hpp>

#include <PPCLexer/LexedFile.hpp>

#include <PPCLib/SymbolMap/PPCSymbol.hpp>

#include <PPCLexer/FileInputs/LoadInput.hpp>

//generate a Pure DTK Token Stream
static inline void GeneratePureDTKTokenStream(const std::filesystem::path& ASMFile, std::vector<PPC::Stage1::Token>& tokenStream,
	const std::vector<PPC::SymbolMap::PPCSymbol>& symbols)
{
	std::string code = "";
	PPC::Lexer::InputLoaders::LoadASM(ASMFile.string(), code);

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
	PPC::Stage1::DumpTokenStream(PPCTokenStreamOutputDir.string() + std::string("/") + filename + PPC_TOKEN_STREAM_FILE_EXTENSION, tokens);
}

//entry point
int main(int args, const char* argv[])
{
	//if no arguments pass a help screen

	//parse the arguments

	//loads the symbol files
	//std::vector<PPC::SymbolMap::PPCSymbol> symbols = PPC::SymbolMap::LoadPPCSymbolMap("C:/Decomps/TOD-Decomp/RawASM/DTKSymbolsNSplits/PureDTKSymbols.ppcmap");

	//gets the PPC Token files
	//const std::vector<std::filesystem::path> files = GetAllPPCTokenFilesInDirectory("C:/Decomps/TOD-Decomp/TypedASM/asm");


	getchar();
	return 0;
}