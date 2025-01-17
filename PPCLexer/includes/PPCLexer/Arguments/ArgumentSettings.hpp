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
		Recomp, //this tells the lexer to purge anything extra, we are using all theses for a recomp
	};

	//defines input type
	enum class InputType
	{
		ASM = 0, //is it a DTK Assembly file
		TokenStream, //is it a pre-existing token stream
		None, //is it nothing and disables this input
	};

	//defines a input directory
	struct ArgumnentSettings_InputDirectory
	{
		InputType type = InputType::None; //is this input type disable or we doing something
		std::filesystem::path inputDirectory = std::filesystem::path(); //the directory to use
	};

	//defines a input type of just singles files
	struct ArgumentSettings_InputSingleFiles
	{
		InputType type = InputType::None; //is this input type disable or we doing something
		std::vector<std::filesystem::path> filpaths;
	};

	//defines the output directory
	struct ArgumentSettings_OutputDirectory
	{
		std::filesystem::path outputDirectory = std::filesystem::path(); //the directory to use as output
	};


	//defines the settings of all the arguments
	struct ArgumentSettings
	{
		LexerMode mode = LexerMode::PureDTK; //what mode is the lexer in, this tells it if it should use extra subpasses
		
		ArgumentSettings_InputSingleFiles singleFileInput; //are we importing single files
		ArgumnentSettings_InputDirectory directoryInput; //are we importing a whole directory
	};
}