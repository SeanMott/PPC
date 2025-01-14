/*
Parses DTK Symbols and Splits into PPC Map files
*/

#include <PPCLib/Logger.hpp>

#include <PPCLib/SymbolMap/PPCSymbol.hpp>

#include <filesystem>
#include <vector>
#include <fstream>

//defines a DTK Symbol value and name parameter pair
struct DTKSymbolParameterValueNamePair
{
	std::string name = "", value = "";
};

//takes a DTK symbol parameter and split it out by the :
static inline DTKSymbolParameterValueNamePair GetValueAndNameOfDTKParamterPair(const std::string& nameValuePair)
{
	DTKSymbolParameterValueNamePair pair;
	bool isDoneWithName = false;

	for (size_t i = 0; i < nameValuePair.size(); ++i)
	{
		//splits the word
		if (nameValuePair[i] == ':')
		{
			isDoneWithName = true;
			continue;
		}

		//adds to either part
		(isDoneWithName == true ? pair.value : pair.name) += nameValuePair[i];
	}

	return pair;
}

//takes a string and parses out the DTK info
static inline void ParseDTKSymbolStringInfo(const std::string& line, PPC::SymbolMap::PPCSymbol& symbol)
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
	symbol.identifier = words[0];
	uint8_t wordIndex = 0;

	//skip the =
	wordIndex += 2;

	//grab the next word as that's our split section and address and remove the semicolon on the end
	std::string split_address = words[wordIndex];
	split_address.resize(split_address.size() - 1);
	wordIndex++;

	//then split it out into the name and value pair
	DTKSymbolParameterValueNamePair splitAddressPair = GetValueAndNameOfDTKParamterPair(split_address);
	symbol.split = splitAddressPair.name;
	symbol.address = splitAddressPair.value;

	//skip the // since that's unneeded data
	wordIndex++;

	//grab all the rest of the parameters and sort them by the first part
	const size_t wordCount = words.size();
	std::vector<DTKSymbolParameterValueNamePair> dataPairs;
	dataPairs.reserve(wordCount - (wordIndex - 1));
	for (wordIndex; wordIndex <wordCount; ++wordIndex)
		dataPairs.emplace_back(GetValueAndNameOfDTKParamterPair(words[wordIndex]));

	//if the start of the name is a @, merge it with a _ whatever the address is
	//since for some reason DTK is dumb about that.
	if (symbol.identifier[0] == '@')
		symbol.identifier += "_" + splitAddressPair.value;

	const size_t dataPairsCount = dataPairs.size();

	//process the type
	for (size_t i = 0; i < dataPairsCount; ++i)
	{
		//parses the type
		if (dataPairs[i].name == "type")
			symbol.type = PPC::Data::ObjectType::ConvertDTKSymbolTypeIntoObjectType(dataPairs[i].value);

		//parses the scope
		else if (dataPairs[i].name == "scope")
			symbol.scope = PPC::Data::Scope::ConvertDTKKeywordStringToScopeType(dataPairs[i].value);

		//parses the size
		else if (dataPairs[i].name == "size")
			symbol.size = dataPairs[i].value;

		//parses the data
		else if (dataPairs[i].name == "data")
			symbol.datatype = dataPairs[i].value;
	}
}

//parses the arguments

//-----have all symbols in one file (default function)

//-----split the symbols into files based on their type: param

//-----split the symbols into files based on their splits

//entry
int main(int args, const char* argv[])
{
	//loads the symbol file
	const std::filesystem::path symbolPath = "C:/Decomps/TOD-Decomp/RawASM/DTKSymbolsNSplits/symbols.txt";

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
	const size_t lineCount = lines.size();
	std::vector<PPC::SymbolMap::PPCSymbol> symbols; symbols.resize(lineCount);
	for (size_t i = 0; i < lineCount; ++i)
		ParseDTKSymbolStringInfo(lines[i], symbols[i]);

	//generate the .ppcmap file
	const std::filesystem::path ppcMap = "C:/Decomps/TOD-Decomp/PPCDTK/PureDTKSymbols.ppcmap";

	//generates map
	nlohmann::json ppcMapSymbols = nlohmann::json::array();
	for (size_t i = 0; i < lineCount; ++i)
		ppcMapSymbols.emplace_back(nlohmann::json{ {"symbolName", symbols[i].identifier}, {"split", symbols[i].split}, {"address", symbols[i].address},
			{"size", symbols[i].size}, {"datatype", symbols[i].datatype}, {"scope", symbols[i].scope}});
	std::ofstream file(ppcMap);
	file << ppcMapSymbols.dump();
	
	getchar();
	return 0;
}