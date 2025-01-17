#pragma once

//defines the arguments the lexer can take in

#include <PPCLexer/Arguments/ArgumentSettings.hpp>

namespace PPC::Lexer::Settings
{
	//defines a flag for the lexer mode

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