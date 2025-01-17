#pragma once

//defines methods for loading files passed into the lexer

#include <PPCLexer/Arguments/ArgumentSettings.hpp>

#include <PPCLib/Token/Token.hpp>

namespace PPC::Lexer::InputLoaders
{
	//defines a input file
	struct InputFile
	{
		Settings::InputType type = Settings::InputType::None;
		std::filesystem::path filepath;
	};

	//loads the desired input type from a whole directory
	static inline std::vector<InputFile> GetAllFilesOfInputTypeFromDirectory(const std::filesystem::path& dir, const Settings::InputType& type)
	{
		const std::string ASMDirectory = dir.string(); //the directory
		const std::string extension = (type == Settings::InputType::ASM ? ".s" : PPC_TOKEN_STREAM_FILE_EXTENSION); //gets the extension


		std::vector<InputFile> files; files.reserve(5);
		for (const auto& entry : std::filesystem::directory_iterator(ASMDirectory))
		{
			if (entry.is_regular_file() && entry.path().extension() == extension)
			{
				InputFile* f = &files.emplace_back(InputFile());
				f->type = type;
				f->filepath = entry;
			}
		}
		return files;
	}

	//loads the translation unit code
	static inline void LoadASM(const std::filesystem::path& filepath, std::string& code)
	{
		FILE* file = fopen(filepath.string().c_str(), "r");
		fseek(file, 0, SEEK_END);
		const size_t codeLength = ftell(file);
		fseek(file, 0, SEEK_SET);
		code.resize(codeLength);
		fread(code.data(), sizeof(char), codeLength, file);
		fclose(file);
	}
}