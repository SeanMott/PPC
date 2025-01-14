/*
Parses DTK Symbols and Splits into PPC Map files
*/

#include <PPCLib/Logger.hpp>

#include <PPCLib/SymbolMap/PPCSymbol.hpp>

#include <vector>

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
	//loads the DTK symbol file
	const std::filesystem::path symbolPath = "C:/Decomps/TOD-Decomp/RawASM/DTKSymbolsNSplits/symbols.txt";
	std::ifstream file(symbolPath);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
		lines.emplace_back(line);

	//process
	const size_t lineCount = lines.size();
	std::vector<PPC::SymbolMap::PPCSymbol> symbols; symbols.resize(lineCount);
	for (size_t i = 0; i < lineCount; ++i)
		ParseDTKSymbolStringInfo(lines[i], symbols[i]);

	//generate the .ppcmap file
	const std::filesystem::path ppcMap = "C:/Decomps/TOD-Decomp/PPCDTK/PureDTKSymbols.ppcmap";
	PPC::SymbolMap::DumpPPCSymbolsToMap(ppcMap, symbols);
	
	//getchar();
	return 0;
}