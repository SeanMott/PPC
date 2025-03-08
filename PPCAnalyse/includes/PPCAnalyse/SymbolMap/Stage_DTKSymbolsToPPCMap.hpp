#pragma once

//defines a stage for converting symbol list from DTK to PPC Map

#include <PPCAnalyse/SymbolMap/DTKSymbolsToPPCSymbolMap.hpp>

#include <fstream>
#include <filesystem>

namespace PPC::Analyse::Stage
{
	//defines a stage for converting a DTK Symbol List To PPC Map
	static inline void Stage_DTKSymbolListToPPCMap(const std::filesystem::path splitsNSymbolsDir, const std::filesystem::path symbolMapDir,
		const bool generateTypeNames, const bool isPretty)
	{
		//convert DTK symbol list into PPC Map
		const std::filesystem::path DTKSymbolFilename = splitsNSymbolsDir.string() + "/symbols.txt";

		//symbols we generate or load
		std::vector<PPC::SymbolMap::PPCSymbol> symbols;

		//loads the DTK symbol file
		std::ifstream file(DTKSymbolFilename.string());
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(file, line))
			lines.emplace_back(line);

		//process
		const size_t lineCount = lines.size();
		symbols.clear(); symbols.resize(lineCount);
		for (size_t i = 0; i < lineCount; ++i)
			PPC::Symbols::ParseDTKSymbolStringInfo(lines[i], symbols[i]);
		std::vector<PPC::SymbolMap::PPCSymbol> typedSymbols = symbols;

		////if it's a existing PPC Map
		//else if (!settings.existingPPCMapFile.empty())
		//	symbols = PPC::SymbolMap::LoadPPCSymbolMap(settings.existingPPCMapFile);

		//if it's a Code Warror Map

		//if we're generating new type names
		if (generateTypeNames)
		{
			size_t pureFloatTypes = 0, pureDoubleTypes = 0, pureStrTypes = 0, pureByteTypes = 0, pureByte2Types = 0, pureByte4Types = 0;

			const size_t symbolCount = symbols.size();
			PPC::SymbolMap::SymbolMapType type = PPC::SymbolMap::SymbolMapType::Null;
			for (size_t i = 0; i < symbolCount; ++i)
			{
				//skip
				if (symbols[i].identifier.size() < 4 || symbols[i].identifier[0] != 'l' || symbols[i].identifier[1] != 'b' || symbols[i].identifier[2] != 'l' ||
					symbols[i].identifier[3] != '_')
					continue;

				if (PPC::SymbolMap::IsSymbolMapType(symbols[i].datatype.c_str(), type))
				{
					switch (type)
					{
					case PPC::SymbolMap::SymbolMapType::Byte:
						pureByteTypes++;
						typedSymbols[i].identifier = "LBL_STRUCT_BYTE_" + std::to_string(pureByteTypes);
						break;

					case PPC::SymbolMap::SymbolMapType::Byte2:
						pureByte2Types++;
						typedSymbols[i].identifier = "LBL_STRUCT_BYTE2_" + std::to_string(pureByte2Types);
						break;

					case PPC::SymbolMap::SymbolMapType::Byte4:
						pureByte4Types++;
						typedSymbols[i].identifier = "LBL_STRUCT_BYTE4_" + std::to_string(pureByte4Types);
						break;

					case PPC::SymbolMap::SymbolMapType::String:
						pureStrTypes++;
						typedSymbols[i].identifier = "LBL_STRUCT_STRING_" + std::to_string(pureStrTypes);
						break;

					case PPC::SymbolMap::SymbolMapType::Float:
						pureFloatTypes++;
						typedSymbols[i].identifier = "LBL_STRUCT_FLOAT_" + std::to_string(pureFloatTypes);
						break;

					case PPC::SymbolMap::SymbolMapType::Double:
						pureDoubleTypes++;
						typedSymbols[i].identifier = "LBL_STRUCT_DOUBLE_" + std::to_string(pureDoubleTypes);
						break;
					}
				}
			}
		}

		//generate the .ppcmap file
		std::filesystem::path ppcMap = std::filesystem::path(symbolMapDir.string() + "/Map" + PPC_MAP_FILE_EXTENSION);
		PPC::SymbolMap::DumpPPCSymbolsToMap(ppcMap, symbols, isPretty);
		ppcMap = std::filesystem::path(symbolMapDir.string() + "/TypedNameMap" + PPC_MAP_FILE_EXTENSION);
		PPC::SymbolMap::DumpPPCSymbolsToMap(ppcMap, typedSymbols, isPretty);
	}
}