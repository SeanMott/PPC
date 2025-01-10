#pragma once

//defines a compiler settings

#include <PPC/Logger.hpp>

namespace PPC::Data
{
	//defines compiler settings
	struct CompilerSettings
	{
		//lexer options
		bool outputDebugASM = false; //tells the lexer to output a debug file dump of the files in sudo-ASM format after all the subpasses
	
		//AST options

		//general settings
	};

	//prints help info for every command
	static inline void CompilerSettings_PrintHelp()
	{
		fmt::print(fmt::fg(fmt::color::green), "Welcome to the Power PC Transcompiler || <Put version info here>\n");
		fmt::print("PPC is a transcompiler/static recompiler created by Sean 'Jas' Mott with help from Wow Jinxy. It's purpose is for converting Game Cube and Wii assembly into C++.");
	}

	//parses the commands
}