#pragma once

//defines a translation file

#include <filesystem>

namespace PPC::Data
{
	//defines a translation unit
	struct TranslationUnit
	{
		std::filesystem::path filepath;

		std::string code = "";
		size_t codeLength = 0;
	
		//loads the translation unit
		inline void LoadCode(const std::filesystem::path& _filepath)
		{
			filepath = _filepath;

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