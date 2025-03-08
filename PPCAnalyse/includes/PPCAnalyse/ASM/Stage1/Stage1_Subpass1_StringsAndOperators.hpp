#pragma once

//defines a subpass in the lexing process
//we split it into a subpass to make parsing the code easier as we take it one step at a time

#include <PPCLib/Token/Token.hpp>

namespace PPC::Analyse::ASM::Stage1::Subpass
{
	//performs subpass 1
	//parses out the string literals, operators, and new lines
	//everything else is defined as a Genaric Token
	std::vector<Token::Token> PerformSubpass1(const std::string& code);
}