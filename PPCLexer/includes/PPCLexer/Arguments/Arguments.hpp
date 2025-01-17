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

	//prints the help page

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