#pragma once

//defines the arguments the lexer can take in

#include <PPCLexer/Arguments/ArgumentSettings.hpp>

namespace PPC::Lexer::Settings
{
	//defines a flag for the lexer mode

	//defines a flag for importing a whole directory of DTK Assembly

	//defines a flag for taking a single DTK Assembly file

	//defines a flag for importing a whole directory of PPC Token Streams

	//defines a flag for importing a single PPC Token Stream file

	//defines a flag for importing a PPC Symbol Map

	//sets the output directory

	//sets the output name (if single files, will increment a 1 after each)
	//if no name is set, it will just use the name of the file it inputed

	//parses the arguments
	static inline ArgumentSettings ParseArguments(const int args, const char* argv[])
	{
		ArgumentSettings settings;


		return settings;
	}
}