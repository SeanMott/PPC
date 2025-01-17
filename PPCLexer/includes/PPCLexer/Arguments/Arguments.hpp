#pragma once

//defines the arguments the lexer can take in

#include <PPCLexer/Arguments/ArgumentSettings.hpp>

namespace PPC::Lexer::Settings
{
	//defines a flag for setting the lexer
#define PPC_LEXER_ARGUMENT_STRING_MODE "-mode"

	//defines a value for the mode flag
#define PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PURE "Pure"
#define PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PUREASM "PureAsm"
#define PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_RECOMP "Recomp"

	//sets the input type
#define PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE "-input"

	//defines a value for the input flag
#define PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_ASM1 "asm"
#define PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_ASM2 "Asm"
#define PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_TOKEN1 "token"
#define PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_TOKEN2 "Token"

	//defines a flag for loading a whole director
#define PPC_LEXER_ARGUMENT_STRING_LOAD_DIRECTORY "-dir"

	//defines a flag for importing a PPC Symbol Map
#define PPC_LEXER_ARGUMENT_STRING_PPC_SYMBOL_MAP "-map"

	//sets the output directory
#define PPC_LEXER_ARGUMENT_STRING_OUT "-out"

	//sets the output name (if single files, will increment a 1 after each)
	//if no name is set, it will just use the name of the file it inputed

	//makes the token streams pretty
#define PPC_LEXER_ARGUMENT_STRING_PRETTY "-pretty"

	//defines a info entry for a command
#define PPC_LEXER_PRINT_FORMAT(cmd, valueType, requiredOrNah, desc) \
fmt::print("{} <{}> || {} || {}\n\n", cmd, valueType, requiredOrNah, desc);

	//prints the help screen
	static inline void PrintArgumentHelpScreen()
	{
		PPC_LEXER_PRINT_FORMAT(PPC_LEXER_ARGUMENT_STRING_MODE, "String Value", "Optional",
			"Sets the mode the lexer will perform. This is used regardless if you are importing Token Stream(s) or Assembly."
			"\nAcceptable String Values:\n"
			PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PURE " || Sets the lexer to output a Token Stream that will disable all the subpasses. "
			"The closets to raw DTK Asssembly. Useful if you are doing the inital project generation.\n"
			PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_RECOMP " || Sets the lexer to output a Token Stream and have all the subpasses. "
			"This version of a Token Stream is most optimized for generating a Static Recomp. This is useful if you don't care to generate DTK Assembly with type info\n"
			PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PUREASM " || Sets the lexer to output DTK Assembly. Is identical to using " PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PURE ". "
			"This mode exists if you intend to generate DTK Assembly with type information. Should be used with a Token Stream and PPC Symbol Map that has had it's type info generated. "
			"See the Symbol Cruncher for how to generate a Symbol Map with type info.\n"
			"If this flag is not set, default mode is " PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PURE ".");

		PPC_LEXER_PRINT_FORMAT(PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE, "String Value", "Optional",
			"Sets if the lexer will load Token Stream(s) or DTK Assembly."
			"\nAcceptable String Values:\n"
			PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_ASM1 " or " PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_ASM2 " || Both will tell the lexer to load Assembly files.\n"
			PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_TOKEN1 " or " PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_TOKEN2 " || Both will tell the lexer to load Token Stream files.\n"
			"If the flag is not set, the default input type is Assembly.")

		PPC_LEXER_PRINT_FORMAT(PPC_LEXER_ARGUMENT_STRING_LOAD_DIRECTORY, "Directory Full Path", "Required",
			"Full path to the directory you would like to load Assembly or Token Streams from.")

		PPC_LEXER_PRINT_FORMAT(PPC_LEXER_ARGUMENT_STRING_PPC_SYMBOL_MAP, "File Full Path", "Required", "File path to the PPC Map file to use.")

		PPC_LEXER_PRINT_FORMAT(PPC_LEXER_ARGUMENT_STRING_OUT, "Directory Full Path", "Required",
			"Full path to the directory you would like to dump the Token Stream or Assembly into.")

		PPC_LEXER_PRINT_FORMAT(PPC_LEXER_ARGUMENT_STRING_PRETTY, "NONE", "Optional",
			"When this flag is passed in, outputted Token Streams will be made more human friendly. Will increase the size of the files. Not recommended for recomp.")
	}

	//prints that there was a error with a argument
	static inline void PrintArgumentError(const std::string& argument, const std::string& desc)
	{
		fmt::print("ARGUMENT INVALID ERROR, ABORTING OPERATION!!!!!!!!!!!!\nArgument: \"{}\" || {}\n", argument, desc);
	}

	//parses the arguments
	static inline ArgumentSettings ParseArguments(const int args, const char* argv[])
	{
		ArgumentSettings settings;

		for (size_t i = 1; i < args; ++i)
		{
			//sets the directory to load
			if (!strcmp(argv[i], PPC_LEXER_ARGUMENT_STRING_LOAD_DIRECTORY))
			{
				//checks if we have the next argument, if not throw a error

				//sets the argument
				i++;

				settings.input.paths.resize(1);
				settings.input.isLoadingWholeDirectories = true;
				settings.input.paths[0] = argv[i];
			}

			//sets the mode we are using
			else if (!strcmp(argv[i], PPC_LEXER_ARGUMENT_STRING_MODE))
			{
				//checks if we have the next argument, if not throw a error

				//sets the argument
				i++;

				const char* m = argv[i];

				//if Pure DTK
				if (!strcmp(m, PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PURE))
				{
					fmt::print("Mode Set: Pure\n");
					settings.mode = Settings::LexerMode::PureDTK;
				}

				//if it's Pure and we're regening the ASM
				else if (!strcmp(m, PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_PUREASM))
				{
					fmt::print("Mode Set: Pure ASM\n");
					settings.mode = Settings::LexerMode::PureDTK_GenASM;
				}

				//if recomp
				else if (!strcmp(m, PPC_LEXER_ARGUMENT_STRING_MODE_VALUE_RECOMP))
				{
					fmt::print("Mode Set: Recomp\n");
					settings.mode = Settings::LexerMode::Recomp;
				}

				//if unknown
				else
				{
					fmt::print("Could not parse Mode flag, Mode is defaulting to DTK Pure\n");
					settings.mode = Settings::LexerMode::PureDTK;
				}
			}

			//sets the input type we are using
			else if (!strcmp(argv[i], PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE))
			{
				//checks if we have the next argument, if not throw a error

				//sets the argument
				i++;

				const char* m = argv[i];

				//if ASM
				if (!strcmp(m, PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_ASM1) || !strcmp(m, PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_ASM2))
				{
					fmt::print("Input Mode Set: ASM\n");
					settings.input.type = InputType::ASM;
				}

				//if it's token streams
				else if (!strcmp(m, PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_TOKEN1) || !strcmp(m, PPC_LEXER_ARGUMENT_STRING_INPUT_TYPE_VALUE_TOKEN2))
				{
					fmt::print("Input Mode Set: Token Streams\n");
					settings.input.type = InputType::TokenStream;
				}

				//if unknown
				else
				{
					fmt::print("Could not parse Input Type flag, defaulting to ASM\n");
					settings.input.type = InputType::ASM;
				}
			}

			//sets the symbol map we are using
			else if (!strcmp(argv[i], PPC_LEXER_ARGUMENT_STRING_PPC_SYMBOL_MAP))
			{
				//checks if we have the next argument, if not throw a error

				//sets the argument
				i++;
				settings.input.symbolMap = argv[i];
			}

			//sets the output directory
			else if (!strcmp(argv[i], PPC_LEXER_ARGUMENT_STRING_OUT))
			{
				//checks if we have the next argument, if not throw a error

				//sets the argument
				i++;
				settings.output.outputDirectory = argv[i];
			}

			//makes the token stream pretty and more human readable
			else if (!strcmp(argv[i], PPC_LEXER_ARGUMENT_STRING_PRETTY))
				settings.output.isPretty = true;
		}

		return settings;
	}
}