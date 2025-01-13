/*
Parses DTK Symbols and Splits into PPC Map files
*/

#include <PPCLib/Logger.hpp>

#include <vector>
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
	std::vector<std::string> words; words.reserve(5);
	std::string word = "";
	for (size_t i = 0; i < line.size(); ++i)
	{
		if (line[i] == ' ')
		{
			words.emplace_back(word);
			word = "";
			continue;
		}

		word += line[i];
	}
	words.emplace_back(word);

	//grab the first word as that is our identifier
	const std::string identifier = words[0];
	uint8_t wordIndex = 0;
	fmt::print(fmt::fg(fmt::color::beige), "Symbol Name: {} || ", identifier);

	//skip the =
	wordIndex += 2;

	//grab the next word as that's our split section and address
	const std::string split_address = words[wordIndex];
	wordIndex++;
	fmt::print(fmt::fg(fmt::color::crimson), "Split Address: {} || ", split_address);

	//split the word out into it's section and address

	//chop off the ; at the end of this word

	//skip the // since that's unneeded data
	wordIndex++;

	//grab all the rest of the parameters and sort them by the first part
	for (wordIndex; wordIndex < words.size(); ++wordIndex)
		fmt::print(fmt::fg(fmt::color::aqua), " {} || ", words[wordIndex]);
	fmt::print("\n");

	//if the start of the name is a @, merge it with a _ whatever the address is
	//since for some reason DTK is dumb about that.
}

//parses the arguments

//entry
int main(int args, const char* argv[])
{
	//loads the symbol file
	std::vector<std::string> lines = {
		"@1249 = .data:0x80049628; // type:object size:0x84 scope:local",
		"jumptable_800496AC = .data:0x800496AC; // type:object size:0x84 scope:local",
		"jumptable_80049730 = .data:0x80049730; // type:object size:0xE0 scope:local",
		"jumptable_80049810 = .data:0x80049810; // type:object size:0x44 scope:local",
		"lbl_80049858 = .data:0x80049858; // type:object size:0x88",
		"jumptable_800498E0 = .data:0x800498E0; // type:object size:0x1C scope:local",
		"jumptable_800498FC = .data:0x800498FC; // type:object size:0x1C scope:local",
		"gTRKRestoreFlags = .data:0x80049918; // type:object size:0x9 scope:global data:byte",
		"gTRKExceptionStatus = .data:0x80049924; // type:object size:0x10 scope:local data:4byte",
		"lbl_80049934 = .data:0x80049934; // type:object size:0x14 data:4byte",
		"lbl_80049948 = .data:0x80049948; // type:object size:0x40 data:4byte",
		"gDBCommTable = .data:0x80049988; // type:object size:0x1C scope:global data:4byte",
		"lbl_800499C0 = .bss:0x800499C0; // type:object size:0x4 data:4byte",
		"lbl_800499C4 = .bss:0x800499C4; // type:object size:0x1C data:4byte",
		"DriveInfo = .bss:0x800499E0; // type:object size:0x20 scope:local",
		"__OSErrorTable = .bss:0x80049A30; // type:object size:0x44 scope:global data:4byte",
		"lbl_80049A80 = .bss:0x80049A80; // type:object size:0x20",
		"Scb = .bss:0x80049AA0; // type:object size:0x54 scope:local data:4byte",
		"DBQueryData = .text:0x8002D684; // type:function size:0x9C scope:global",
		"DBInitInterrupts = .text:0x8002D720; // type:function size:0x54 scope:global",
		"DBInitComm = .text:0x8002D774; // type:function size:0x78 scope:global",
		"fn_8002D7EC = .text:0x8002D7EC; // type:function size:0x40",
		"fn_8002D82C = .text:0x8002D82C; // type:function size:0x3C",
		"fn_8002D868 = .text:0x8002D868; // type:function size:0xAC",
		"fn_8002D914 = .text:0x8002D914; // type:function size:0xDC",
		"fn_8002D9F0 = .text:0x8002D9F0; // type:function size:0xDC",
		"fn_8002DACC = .text:0x8002DACC; // type:function size:0xAC",
		"fn_8002DB78 = .text:0x8002DB78; // type:function size:0x298",
		"Hu_IsStub = .text:0x8002DE10; // type:function size:0x8 scope:weak"
	};

	//splits it out on threads and process
	for (size_t i = 0; i < lines.size(); ++i)
		ParseDTKSymbolStringInfo(lines[i]);

	//generate the .ppcmap file

	getchar();
	return 0;
}