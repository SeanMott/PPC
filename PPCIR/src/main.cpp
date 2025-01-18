/*
PPC IR, takes a stream of tokens and converts it into IR and sudo-C
*/

#include <PPCLib/SymbolMap/PPCSymbol.hpp>

//defines compiler settings
struct IRSettings
{
	std::filesystem::path symbolMap = "";
};

//entry point
int main(int args, const char* argv)
{
	//parses arguments

	//loads symbol map

	//load the token streams and merge into one token stream

	//pass 1: take all Object and Function definitions and condense them into their own Nodes
	//expand the Symbol Map if we run into anything not in there

	//pass 2: generate the jump label offsets and furthur split functions into their jump labels

	//pass 3: generate variable names for each struct definition and resolve any function poiners

	//pass 4:

	//spit out sudo-C
}