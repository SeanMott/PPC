#pragma once

//defines dumping a token stream

#include <PPCLexer/Token.hpp>

#include <fstream>

namespace PPC::Lexer
{
	//dumps a token stream
	static inline void DumpTokenStream(const std::vector<Stage1::Token> tokenStream, const std::filesystem::path& dumpPath)
	{
		//coverts everything to a string
		std::string str = "";
		for (size_t i = 0; i < tokenStream.size(); ++i)
		{
			//if string literal
			if(tokenStream[i].type == Stage1::TokenType::Literal_String)
				str += '"' + tokenStream[i].data + '"';

			//if comment
			else if (tokenStream[i].type == Stage1::TokenType::SingleLineComment)
				str += '#' + tokenStream[i].data;

			//if block comment
			else if (tokenStream[i].type == Stage1::TokenType::BlockComment)
				str += "/*" + tokenStream[i].data + "*/";

			else
				str += tokenStream[i].data;

			str += ' ';
		}

		std::fstream f(dumpPath, std::ios::out);
		f.write(str.c_str(), str.size());
	}
}