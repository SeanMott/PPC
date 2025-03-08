#pragma once

//defines functions for extracting functions, structs, and syms from the ASM

#include <vector>
#include <string>

namespace PPC::Analyse::ASM::Stage1
{
	//splits words
	static std::vector<std::string> SplitLineIntoWords(const std::string& line)
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

	//extracts the chunks of code for definition any functions, structs, and syms
	static std::vector<std::string> ExtractDefinitions(const std::string& code)
	{
		std::vector<std::string> defs; defs.reserve(30);

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

		//goes till we find the start of a define and then extract thoses bits into their own funcs
		//searches for the func, structs, and syms defs
		const size_t lineCount = lines.size();
		for (size_t i = 0; i < lineCount; ++i)
		{
			//if it starts with a '.', so we know it's a directive of some kind
			if (lines[i].size() > 3 && lines[i][0] == '.')
			{
				std::vector<std::string> words = SplitLineIntoWords(lines[i]);

				//if .sym def
				if (words[0] == ".sym")
					defs.emplace_back(lines[i]);

				//if .fn def
				else if (words[0] == ".fn")
				{
					std::string def = lines[i] + "\n";

					//fmt::print("Function Def: {}\n", words[1]);
					i++; //skip the prototype

					//goes till the end of the func
					while (i < lineCount)
					{
						words = SplitLineIntoWords(lines[i]);

						//if it's the end of the function
						if (words[0] == ".endfn")
						{
							def += lines[i];
							break;
						}

						//strips comments
						const size_t lineLength = lines[i].size();
						std::string cleanedLine = "";
						for (size_t c = 0; c < lineLength; ++c)
						{
							//if we run into a "/*" go till the end of it or the line
							if (c + 1 < lineLength && lines[i][c] == '/' && lines[i][c + 1] == '*')
							{
								c += 2; //goes to the start of the comment

								//strip it out, leaving only the wanted stuff
								while (c < lineLength)
								{
									//if we reached the end
									if (c + 1 < lineLength && lines[i][c] == '*' && lines[i][c + 1] == '/')
									{
										c += 2;
										break;
									}

									c++;
								}
							}

							//adds the char
							if (c < lineLength)
								cleanedLine += lines[i][c];
						}

						//strips the extra tabs
						while (cleanedLine[0] == '\t')
							cleanedLine.erase(cleanedLine.begin());

						//if it's hidden we skip
						if (words[0] == ".hidden")
						{
							i++;
							continue;
						}

						//if it's # comment we skip
						if (words[0][0] == '#')
						{
							i++;
							continue;
						}

						//adds the cleaned line
						//fmt::print("{}\n", cleanedLine);
						def += cleanedLine + "\n";

						i++;
					}

					defs.emplace_back(def);
				}

				//if .obj def
				else if (words[0] == ".obj")
				{
					//fmt::print("Struct Def: {}\n", words[1]);
					std::string def = lines[i] + "\n";
					i++; //skip the prototype

					//goes till the end of the struct

					while (i < lineCount)
					{
						words = SplitLineIntoWords(lines[i]);

						if (words[0] == ".endobj")
						{
							def += lines[i];
							break;
						}

						//strips comments
						const size_t lineLength = lines[i].size();
						std::string cleanedLine = "";
						for (size_t c = 0; c < lineLength; ++c)
						{
							//if we run into a "/*" go till the end of it or the line
							if (c + 1 < lineLength && lines[i][c] == '/' && lines[i][c + 1] == '*')
							{
								c += 2; //goes to the start of the comment

								//strip it out, leaving only the wanted stuff
								while (c < lineLength)
								{
									//if we reached the end
									if (c + 1 < lineLength && lines[i][c] == '*' && lines[i][c + 1] == '/')
									{
										c += 2;
										break;
									}

									c++;
								}
							}

							//adds the char
							if (c < lineLength)
								cleanedLine += lines[i][c];
						}

						//strips the extra tabs
						while (cleanedLine[0] == '\t')
							cleanedLine.erase(cleanedLine.begin());

						//if it's hidden we skip
						if (words[0] == ".hidden")
						{
							i++;
							continue;
						}

						//else we add line
						else
							def += cleanedLine + "\n";

						i++;
					}

					defs.emplace_back(def);
				}
			}
		}

		return defs;
	}
}