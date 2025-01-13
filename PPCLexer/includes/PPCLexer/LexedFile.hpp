#pragma once

//defines a lexed file

#include <PPCLexer/Token.hpp>

#include <filesystem>

namespace PPC::Lexer
{
	//defines a function token stream

	//defines a object token stream

	//defines a lexed file
	struct LexedFile
	{
		std::filesystem::path ASMFile; //the OG Assembly file that generated this

		//the map of identifiers

		//the map of string literals

		//the rest of the tokens
		std::vector<Stage1::Token> tokens;

		//replaces every identifier 
	};
}