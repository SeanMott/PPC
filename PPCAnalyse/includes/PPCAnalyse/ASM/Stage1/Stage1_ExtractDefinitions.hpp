#pragma once

//defines functions for extracting functions, structs, and syms from the ASM

#include <PPCLib/Logger.hpp>

#include <vector>
#include <string>

namespace PPC::Analyse::ASM::Stage1
{
	//splits words
	static inline std::vector<std::string> SplitLineIntoWords(const std::string& line)
	{
		std::vector<std::string> words; words.reserve(4);
		uint32_t lineIndex = 0;
		words.emplace_back(std::string());

		for (size_t i = 0; i < line.size(); ++i)
		{
			//if space
			if (line[i] == ' ')
			{
				lineIndex++;
				words.emplace_back(std::string());
			}

			//adds char
			else
				words[lineIndex] += line[i];
		}

		return words;
	}

	//splits a block of code into lines
	static inline std::vector<std::string> SplitTextIntoLines(const std::string& code)
	{
		//splits the code into lines
		const size_t codeLength = code.size();
		std::vector<std::string> lines; lines.reserve(codeLength);
		std::string line = "";
		for (size_t i = 0; i < codeLength; ++i)
		{
			//if new line
			if (code[i] == '\n')
			{
				lines.emplace_back(line);
				line = "";
			}

			//adds char
			else
				line += code[i];
		}

		return lines;
	}

	//extracts the chunks of code for definition any functions, structs, and syms
	static inline void ExtractDefinitions(const std::string& code,
		std::vector<std::string>& funcStrs, std::vector<std::string>& structStrs)
	{
		//purns everything that isn't a function, struct, or sym define
		funcStrs.reserve(15); structStrs.reserve(15);
		std::vector<std::string> lines = SplitTextIntoLines(code);
		const size_t lineCount = lines.size();
		for (size_t i = 0; i < lineCount; ++i)
		{
			//split into words
			std::vector<std::string> words = SplitLineIntoWords(lines[i]);

			//gets if it's the start of something we can define
			enum class DefType
			{
				None = 0,
				Object,
				Function,

				Count
			};
			DefType type = DefType::None;

			//if struct
			if (words[0] == ".obj")
				type = DefType::Object;

			//if function
			else if (words[0] == ".fn")
				type = DefType::Function;

			//if we do a skip-y cuz it ain't the define
			else
				continue;

			//gets the rest of the body
			std::string prunedCode = lines[i] + "\n";
			while (i < lineCount)
			{
				i++;
				words = SplitLineIntoWords(lines[i]);

				//if it's the end of the body
				if (type == DefType::Object && words[0] == ".endobj" || type == DefType::Function && words[0] == ".endfn")
				{
					prunedCode += lines[i]; //add it so we can clean the token stream afterwards
					//prunedCode.resize(prunedCode.size() - 1); //remove the extra new line
					break;
				}

				//if it starts with ".hidden" skip it
				else if (words[0] == ".hidden")
					continue;

				//otherwise add the line
				prunedCode += lines[i] + "\n";
			}

			//adds the define string
			if (type == DefType::Object)
				structStrs.emplace_back(prunedCode);
			else
				funcStrs.emplace_back(prunedCode);
		}
	}
}