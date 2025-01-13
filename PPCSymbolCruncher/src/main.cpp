/*
Parses DTK Symbols and Splits into PPC Map files
*/

#include <fstream>

//defines a PPC Symbol parsed from the DTK Symbol file
struct PPCSymbol
{
	//the name of the symbol
	//the Symbol ID associated with the Symbol

	//is it a object, function, or label

	//the split section
	//the address it starts
};

//takes a string and parses out the DTK info
static inline void ParseDTKSymbolStringInfo(const std::string& line)
{
	//split the whole line into words by spaces

	//grab the first word as that is our identifier

	//skip the =

	//grab the next word as that's our split section and address

	//split the word out into it's section and address

	//chop off the ; at the end of this word

	//skip the // since that's unneeded data

	//grab all the rest of the parameters and sort them by the first part
}

//parses the arguments

//entry
int main(int args, const char* argv[])
{
	//loads the symbol file

	//splits it out on threads and process

	//generate the .ppcmap file

	return 0;
}