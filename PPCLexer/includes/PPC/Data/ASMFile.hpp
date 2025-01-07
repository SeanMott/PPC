#pragma once

//defines a ASM File

#include <filesystem>

namespace PPC::Data
{
	//defines a ASM file
	struct ASMFile
	{
		std::filesystem::path filepath;

		std::string code = "";
		size_t codeLength = 0;
	
		//sets the raw ASM this TU is associated with
		inline void SetASM(const std::filesystem::path& _filepath)
		{
			filepath = _filepath;
		}

		//loads the translation unit code
		inline void LoadASM()
		{
			FILE* file = fopen(filepath.string().c_str(), "r");
			fseek(file, 0, SEEK_END);
			codeLength = ftell(file);
			fseek(file, 0, SEEK_SET);
			code.resize(codeLength);
			fread(code.data(), sizeof(char), codeLength, file);
			fclose(file);
		}
	};
}