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
struct ArgumentSettings
{
	bool isPretty = false;

	std::filesystem::path DTKSymbolFile = std::filesystem::path(), PPCMapOutputDir = std::filesystem::path(), existingPPCMapFile = std::filesystem::path();
	std::string mapName = "Map";
};

//-----ARGUMENTS----//

//takes a DTK Symbol File
#define PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_SYMBOLS "-symbols"

//takes a Code Warror Map and parses it out
#define PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_CODE_WARROR_MAP "-codeWarriorMap"

//takes a existing PPC Map
#define PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_PPC_MAP "-map"

//sets the output directory of the new PPC Map
#define PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_OUTPUT_DIR "-out"

//sets the name of the new PPC Map
#define PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_MAP_NAME "-name"

//sets if the PPC Map should be formated for human readability or not
#define PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_IS_PRETTY "-pretty"

//takes all the Objects and changes them to their name. This is not reccomanded as a first pass when converting DTK.
#define PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_TYPE_OBJ_NAME "-generateTypeNames"

//-----ARGUMENT SUPPORT MACROS AND FUNCTIONS---------//

//defines a info entry for a command
#define PPC_SYMBOL_CRUNCHER_PRINT_FORMAT(cmd, valueType, requiredOrNah, desc) \
fmt::print("{} <{}> || {} || {}\n\n", cmd, valueType, requiredOrNah, desc);

//prints the help screen
static inline void PrintArgumentHelpScreen()
{
	PPC_SYMBOL_CRUNCHER_PRINT_FORMAT(PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_SYMBOLS, "Full File Path", "Required",
		"Full path to the DTK generated Symbol File.")

		PPC_SYMBOL_CRUNCHER_PRINT_FORMAT(PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_PPC_MAP, "Full File Path", "Optional",
		"Full path to a existing PPC Map. If symbols is also passed in. "
		"It will execute instead. So either " PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_SYMBOLS " or " PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_PPC_MAP " should be used ALONE to not cause conflicts.")

	PPC_SYMBOL_CRUNCHER_PRINT_FORMAT(PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_OUTPUT_DIR, "Directory Full Path", "Required",
		"Full path to the directory you would like the PPC Map outputted to.")

	PPC_SYMBOL_CRUNCHER_PRINT_FORMAT(PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_MAP_NAME, "Name String", "Optional", "Name of the PPC Map file outputted. Defaults to \"Map\".")

	PPC_SYMBOL_CRUNCHER_PRINT_FORMAT(PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_IS_PRETTY, "NONE", "Optional", "Makes the map output in a more human friendly way of reading, defaults to off.")

	PPC_SYMBOL_CRUNCHER_PRINT_FORMAT(PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_TYPE_OBJ_NAME, "NONE", "Optional", 
		"When this flag is passed in, all Object Symbols will have their Datatype counted in a running total. Ie if there are 12 \"4Byte\"s and 3 \"String\"s and so forth. "
		"They will all be tracked in a global count. Once every Datatype is counted, a second pass of the Symbols will be performed. "
		"If the Object Symbol starts with \"lbl_\", it will have it's name changed to specific it's type. For example thoses 12 Symbols with \"4Byte\" as their Datatype. "
		"Will have their name changed to \"LBL_OBJECT_4BYTE_XXXX\". Where XXXX is the current, going from 1 to 12.\n\n"
		"This flag is not recommended to be passed when first converting DTK Symbols and Splits into a PPC Map. "
		"This flag is meant for use AFTER DTK Symbols have been converted into a PPC Map. AND the PPC Lexer has generated the inital Token Streams from the ASM. "
		"Once those previous steps are done, this flag can be used to make reading Object's easier. As the Token Streams store all Identifiers via a ID. "
		"Meaning the PPC Maps can have names freely changed without causing issues with builds.")
}

//prints that there was a error with a argument
static inline void PrintArgumentError(const std::string& argument, const std::string& desc)
{
	fmt::print("ARGUMENT INVALID ERROR, ABORTING OPERATION!!!!!!!!!!!!\nArgument: \"{}\" || {}\n", argument, desc);
}

//parses the arguments
static inline ArgumentSettings ParseArguments(const int args, const char* argv[])
{
	ArgumentSettings settings;
	for (size_t i = 1; i < args; ++i)
	{
		//symbols argument
		if (!strcmp(argv[i], PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_SYMBOLS))
		{
			//checks if we have the next argument, if not throw a error

			//sets the argument
			i++;
			settings.DTKSymbolFile = argv[i];
		}

		//exisitng PPC Map argument
		else if (!strcmp(argv[i], PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_PPC_MAP))
		{
			//checks if we have the next argument, if not throw a error

			//sets the argument
			i++;
			settings.existingPPCMapFile = argv[i];
		}

		//output directory
		else if (!strcmp(argv[i], PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_OUTPUT_DIR))
		{
			//checks if we have the next argument, if not throw a error

			//sets the argument
			i++;
			settings.PPCMapOutputDir = argv[i];
		}

		//map name
		else if (!strcmp(argv[i], PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_MAP_NAME))
		{
			//checks if we have the next argument, if not throw a error

			//sets the argument
			i++;
			settings.mapName = argv[i];
		}

		//is pretty
		else if (!strcmp(argv[i], PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_IS_PRETTY))
			settings.isPretty = true;
	}

	return settings;
}

//entry
int main(int args, const char* argv[])
{
	//if no arguments
	if (args < 2)
	{
		fmt::print(fmt::fg(fmt::color::alice_blue), "PPC Symbol Cruncher");
		fmt::print(fmt::fg(fmt::color::orange), " is a tool for importing symbol lists into a format the PPC Toolchain can use.");

		fmt::print("\n\n----HOW TO USE----\n");
		
		fmt::print("Converting a DTK Symbol list to a PPC Map.\n");
		fmt::print("SymbolCruncher.exe {} \"DTKSplitsNSymbols/Symbols.txt\" {} \"DTKSplitsNSymbols\"\n\n",
			PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_SYMBOLS, PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_OUTPUT_DIR);

		fmt::print("Generating Obj Symbol Names from Types.\n");
		fmt::print("SymbolCruncher.exe {} \"DTKSplitsNSymbols/PureDTKSymbols.ppcmap\" {} \"DTKSplitsNSymbols\" {} \"TypedDTKSymbols\" {}\n\n",
			PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_PPC_MAP, PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_OUTPUT_DIR,
			PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_MAP_NAME, PPC_SYMBOL_CRUNCHER_ARGUMENT_STR_TYPE_OBJ_NAME);

		fmt::print("----ARGUMENT LIST----\n\n");
		
		PrintArgumentHelpScreen(); //prints the list of commands

		getchar();
		return 0;
	}

	//parse the arguments
	ArgumentSettings settings = ParseArguments(args, argv);

	//symbols we generate or load
	std::vector<PPC::SymbolMap::PPCSymbol> symbols;

	//if it's a DTK Map
	if (!settings.DTKSymbolFile.empty())
	{
		//loads the DTK symbol file
		std::ifstream file(settings.DTKSymbolFile);
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(file, line))
			lines.emplace_back(line);

		//process
		const size_t lineCount = lines.size();
		symbols.clear(); symbols.resize(lineCount);
		for (size_t i = 0; i < lineCount; ++i)
			ParseDTKSymbolStringInfo(lines[i], symbols[i]);
	}

	//if it's a existing PPC Map
	else if (!settings.existingPPCMapFile.empty())
		symbols = PPC::SymbolMap::LoadPPCSymbolMap(settings.existingPPCMapFile);

	//if it's a Code Warror Map
	
	//generate the .ppcmap file
	const std::filesystem::path ppcMap = std::filesystem::path(settings.PPCMapOutputDir.string() + "/" + settings.mapName + PPC_MAP_FILE_EXTENSION);
	PPC::SymbolMap::DumpPPCSymbolsToMap(ppcMap, symbols, settings.isPretty);

	//getchar();
	return 0;
}