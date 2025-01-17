#pragma once

//defines argument settings passed into the lexer

#include <vector>
#include <filesystem>

namespace PPC::Lexer::Settings
{
	//defines the mode of the lexer
	enum class LexerMode
	{
		PureDTK = 0, //this will tell the lexer to not use any extra subpasses and perserve the raw DTK Assembly
		PureDTK_GenASM, //this is just like the Pure DTK, but won't dump tokens and instead spit back out ASM
		Recomp, //this tells the lexer to purge anything extra, we are using all theses for a recomp
	};

	//defines input type
	enum class InputType
	{
		ASM = 0, //is it a DTK Assembly file
		TokenStream, //is it a pre-existing token stream
		None, //is it nothing and disables this input
	};

	//defines the output settings
	struct ArgumentSettings_Output
	{
		bool isPretty = false; //makes the outputted token stream more human readable

		std::filesystem::path outputDirectory = std::filesystem::path(); //the directory to use as output
	};

	//defines the input settings
	struct ArgumentSettings_Input
	{
		InputType type = InputType::ASM; //is it assembly or token streams
		bool isLoadingWholeDirectories = true; //is it single files or directories
		std::vector<std::filesystem::path> paths; //the directories or files

		std::filesystem::path symbolMap = std::filesystem::path(); //the symbol map we are using
	};

	//defines the settings of all the arguments
	struct ArgumentSettings
	{
		LexerMode mode = LexerMode::PureDTK; //what mode is the lexer in, this tells it if it should use extra subpasses
		
		ArgumentSettings_Input input; //defines data for our inputs
		ArgumentSettings_Output output; //defines the data for our outputs
	};
}