/*
PPC Lexer that converts DTK Raw Assembly into a stream of tokens
*/

#include <filesystem>

#include <PPCLexer/Subpasses/Subpass1.hpp>
#include <PPCLexer/Subpasses/Subpass2.hpp>
#include <PPCLexer/Subpasses/SubpassExtraStripping.hpp>

#include <PPCLib/SymbolMap/PPCSymbol.hpp>

#include <PPCLexer/Arguments/Arguments.hpp>
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

//entry point
int main(int args, const char* argv[])
{
	//if no arguments pass a help screen
	if (args < 2)
	{
		fmt::print("PPC Lexer || Created by Sean 'Jas' Mott || Version: <put stuff here>\n");
		fmt::print("PPC Lexer is a tool for importing DTK Assembly and exporting Token Streams used by the rest of the PPC Toolchain.\n\n");

		PPC::Lexer::Settings::PrintArgumentHelpScreen();

		return 1;
	}

	//parse the arguments
	PPC::Lexer::Settings::ArgumentSettings settings = PPC::Lexer::Settings::ParseArguments(args, argv);

	//checks the output and input directory exists

	//check that the symbol map is a PPC Symbol Map, if not throw a error to the user

	//load symbol map
	const std::vector<PPC::SymbolMap::PPCSymbol> symbols = PPC::SymbolMap::LoadPPCSymbolMap(settings.input.symbolMap); //loads the PPC Symbols

	//loads the files
	std::vector<PPC::Lexer::InputLoaders::InputFile> inputFiles = PPC::Lexer::InputLoaders::GetAllFilesOfInputTypeFromDirectory(settings.input.paths[0], settings.input.type);
	const size_t fileCount = inputFiles.size();
	std::vector<std::vector<PPC::Stage1::Token>> tokenStreams; tokenStreams.resize(fileCount);

	for (size_t i = 0; i < fileCount; ++i)
	{
		//if they're assembly, parse em out into the pure first
		if (inputFiles[i].type == PPC::Lexer::Settings::InputType::ASM)
			GeneratePureDTKTokenStream(inputFiles[i].filepath, tokenStreams[i], symbols);

		//if they're token streams, handle the subpasses
		else if (inputFiles[i].type == PPC::Lexer::Settings::InputType::TokenStream)
			tokenStreams[i] = PPC::Stage1::LoadTokenStream(inputFiles[i].filepath);

		//perform the other subpasses, if we're in recomp mode
		if (settings.mode == PPC::Lexer::Settings::LexerMode::Recomp)
		{
			//strips invalid instructions
			tokenStreams[i] = PPC::Lexer::Subpass::ExtraSubpass_RemoveInvalidInstructions(tokenStreams[i]);
			
			//strips comments, file/include, and section data
			tokenStreams[i] = PPC::Lexer::Subpass::ExtraSubpass_RemoveFileAndIncludes(tokenStreams[i]);
		}

		//dump the tokens or generate the ASM
		if (settings.mode != PPC::Lexer::Settings::LexerMode::PureDTK_GenASM) //dumps token streams
		{
			const std::filesystem::path dumpFP = settings.output.outputDirectory.string() + "/" + inputFiles[i].filepath.filename().stem().string() + PPC_TOKEN_STREAM_FILE_EXTENSION;
			PPC::Stage1::DumpTokenStream(dumpFP, tokenStreams[i], settings.output.isPretty);
		}
		else //dumps ASM
		{
			const std::filesystem::path dumpFP = settings.output.outputDirectory.string() + "/" + inputFiles[i].filepath.filename().stem().string() + ".s";
			PPC::Stage1::DumpASMFromTokenStream(dumpFP, tokenStreams[i], symbols);
		}
	}

	return 0;
}