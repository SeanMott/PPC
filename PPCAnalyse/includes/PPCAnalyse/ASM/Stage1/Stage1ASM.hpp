#pragma once

/*
Stage 1 of the PPC Toolchain Process

Stage 1 takes the outputted DTK Assembly and the parsed symbols.
It then goes through the assembly, extracting any of the object, sym, and function defines.

Then breaks the code into a series of tokens.
Splitting out any operators, string literals, digit literals, keywords, instructions, jump labels, and comments.

With a free stream of tokens, we then prune anything not inside the function and object definitions.
This removes the extra stuff DTK generates so the ASM can compile back into a byte for byte dol.

Finally all the refrences to identifiers in the symbol list is converted into a Symbol ID.
This is so we can freely change the names without having to parse more text.
We want to replace the names since the weird @ ones or ones wrapped in "" are not ease to convert to C++.

With every identifier marked out, we can then perform a second pass that converts any jump labels into unique IDs.
This builds mini jump tables inside the functions. This will later be used alonside their origianl memory location.
To resolve all the function pointers that use relative addresses.

The final object is a tree of all the tokens making up our desired code.
This tree has IDs replacing every name and can freely be written to disc to be re-used or passed back through the later stages for more parsing.
*/

#include <string>

namespace PPC::Analyse::ASM::Stage1
{
	//defines the first stage for turning Power PC into a recomp
	void PerformStage1(const std::string& code);
}