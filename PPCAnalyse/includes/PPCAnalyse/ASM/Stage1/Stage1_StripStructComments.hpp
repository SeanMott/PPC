#pragma once

//strips comments in structs since they're unneeded
//unlike function comments which give us a memory map

#include <string>
#include <vector>

namespace PPC::Analyse::ASM::Stage1
{
	static inline void StripUnneededComments(std::vector<std::string>& structBodyStrs)
	{
		//goes through the structs and strips their comments
		for (size_t i = 0; i < structBodyStrs.size(); ++i)
		{
			bool codeNeededPruning = false;

			size_t codeLength = structBodyStrs[i].size();
			for (size_t c = 0; c < codeLength; ++c)
			{
				if (c + 1 < codeLength && structBodyStrs[i][c] == '/' && structBodyStrs[i][c + 1] == '*')
				{
					const size_t commentStartIndex = c;

					//goes till the end of the comment
					while (c < codeLength)
					{
						c++;

						if (c + 1 < codeLength && structBodyStrs[i][c] == '*' && structBodyStrs[i][c + 1] == '/')
						{
							c++;
							break;
						}
					}

					const size_t commentEndIndex = c;

					//erases the comment and reset the char counter
					structBodyStrs[i].erase(structBodyStrs[i].begin() + commentStartIndex, structBodyStrs[i].begin() + commentEndIndex + 1);
					codeLength = structBodyStrs[i].size();
					c = -1;
				}
			}
		}
	}
}