#pragma once

//defines argument settings

#include <filesystem>

namespace PPC::Recomp::Arguments
{
	//defines the argument settings
	struct ArgumentSettings
	{
		std::filesystem::path symbolMap = "", //the PPC Symbol map to use
			tokenizedASMDir = "", //the directory of tokenized ASM to load and transcompile
			codeOutputDir = ""; //the output directory for the C++ code
	};
}