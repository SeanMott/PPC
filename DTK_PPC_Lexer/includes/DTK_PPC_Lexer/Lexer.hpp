#pragma once

//defines a lexer for parsing DTK Assembly

#include <string>

namespace PPC::Frontend::DTK
{
	//defines a parser for DTK Assembly
	void ASMParser(const std::string& code);
}