#pragma once

//defines a Token

#include <PPCLib/Logger.hpp>
#include <PPCLibVenders/json.hpp>

#include <PPCLib/Data/ObjectType.hpp>
#include <PPCLib/Data/Scope.hpp>
#include <PPCLib/Data/MemoryOffset.hpp>
#include <PPCLib/Data/Datatypes.h>
#include <PPCLexer/Data/PPCInstructions.hpp>

#include <vector>
#include <fstream>

namespace PPC::Stage1
{
	//defines a general token type
	enum class TokenType
	{
		Genaric = 0, //this is differant from a identifier and is just a general token we use that stores a blob of string data
		//this is used in earlier subpasses to handle stuff we don't want to parse yet.
		//we parse it out at a later pass when there's less to worry about

		Identifier, //the general identifier

		Symbol_ID, //the symbol identifier ID

		Keyword, //a keyword

		Keyword_Scope, //defines a scope keyword

		Keyword_Object, //defines a object keyword for start and end of structs and funcs and syms/labels

		Keyword_MemoryOffset, //defines a memory offset keyword

		Datatype, //a datatype

		Register, //a register

		Instruction, //defines a instruction

		Literal_String, //the string literal

		Operator, //a operator in the syntax

		SingleLineComment, //a single line # comment
		BlockComment, //a block comment

		NewLine,

		Count
	};

	//defines a specific token type
	enum class SpecificTokenType
	{
		//mic
		Keyword_Alignment,

		//registers
		Register_Int, //if it's a int register
		Register_Float,
		Register_GraphicsQuantized,
		Register_Condition,
		Register_Special,

		Count
	};

	//defines a token
	struct Token
	{
		size_t lineCount = 1, charCount = 0;
		TokenType type = TokenType::Count; //the general type
		SpecificTokenType specificType = SpecificTokenType::Count; //the specific type

		//specific type bits
		Data::Scope::ScopeType scopeType = Data::Scope::ScopeType::None;
		Data::ObjectType::ObjectType objType = Data::ObjectType::ObjectType::None;
		Data::MemoryOffset::MemoryOffsetType memoryOffsetType = Data::MemoryOffset::MemoryOffsetType::None;
		Data::ASM::EInstruction instruction = Data::ASM::EInstruction::eInstruction_nop; //the current instruction
		Data::Datatype::DTKDatatypeType datatype = Data::Datatype::DTKDatatypeType::None;
		uint64_t symbolID = 0; //the symbol ID

		std::string data = "";

		//generates a entry in a JSON Token Stream
		inline nlohmann::json GenerateJSONArrayEntry() const
		{
			return nlohmann::json{ {"type", type}, {"lineCount", lineCount}, {"charCount", charCount},
				{"data", data}, {"specificType", specificType},
				{"scopeType", scopeType}, {"objectType", objType}, {"memoryOffset", memoryOffsetType},
				{"instruction", instruction}, {"datatype", datatype}, {"symbolID", symbolID} };
		}

		//prints the token
		inline void Print() const
		{
			switch (type)
			{
			case TokenType::Genaric:
				fmt::print("Line: {}, Char: {} || Genaric {}\n", lineCount, charCount, data);
				break;

			case TokenType::Keyword:
				fmt::print("Line: {}, Char: {} || Keyword || {}\n", lineCount, charCount, data);
				break;

			case TokenType::Datatype:
				fmt::print("Line: {}, Char: {} || Datatype || {}\n", lineCount, charCount, data);
				break;

			case TokenType::Register:
				fmt::print("Line: {}, Char: {} || Register || {}\n", lineCount, charCount, data);
				break;

			case TokenType::Identifier:
				fmt::print(fmt::fg(fmt::color::blue), "Line: {}, Char: {} || Identifier {}\n", lineCount, charCount, data);
				break;

			case TokenType::Literal_String:
				fmt::print(fmt::fg(fmt::color::azure), "Line: {}, Char: {} || String Literal || \"{}\"\n", lineCount, charCount, data);
				break;

			case TokenType::Symbol_ID:
				fmt::print(fmt::fg(fmt::color::purple), "Line: {}, Char: {} || Symbol || \"{}\" - ID: {}\n", lineCount, charCount, data, symbolID);
				break;

			case TokenType::Instruction:
				fmt::print(fmt::fg(fmt::color::orange), "Line: {}, Char: {} || Instruction {}\n", lineCount, charCount, data);
				break;

			default:
				fmt::print("Line: {}, Char: {} || {}\n", lineCount, charCount, data);
				break;

			}
		}
	};

	//dumps a stream of tokens
	static inline void DumpTokenStream(const std::filesystem::path& tokenStreamFP, const std::vector<Token>& tokens)
	{
		nlohmann::json tokenStream = nlohmann::json::array();
		for (size_t i = 0; i < tokens.size(); ++i)
			tokenStream.emplace_back(tokens[i].GenerateJSONArrayEntry());
		std::ofstream file(tokenStreamFP);
		file << tokenStream.dump();
	}

	//loads a stream of tokens from a file
	static inline std::vector<Token> LoadTokenStream(const std::filesystem::path& tokenStreamFP)
	{
		//loads map
		std::ifstream file(tokenStreamFP);
		nlohmann::json rawTokenStream;
		file >> rawTokenStream;

		//parse into symbol array
		std::vector<Token> tokenStream; tokenStream.reserve(15);
		for (auto& rawToken : rawTokenStream)
		{
			Token* t = &tokenStream.emplace_back(Token());
			t->type = rawToken.at("type").get<TokenType>();
			t->lineCount = rawToken.at("lineCount").get<size_t>();
			t->charCount = rawToken.at("charCount").get<size_t>();
			t->data = rawToken.at("data").get<std::string>();
			t->specificType = rawToken.at("specificType").get<SpecificTokenType>();
			t->scopeType = rawToken.at("scopeType").get<Data::Scope::ScopeType>();
			t->objType = rawToken.at("objectType").get<Data::ObjectType::ObjectType>();
			t->memoryOffsetType = rawToken.at("memoryOffset").get<Data::MemoryOffset::MemoryOffsetType>();
			t->instruction = rawToken.at("instruction").get<Data::ASM::EInstruction>();
			t->datatype = rawToken.at("datatype").get<Data::Datatype::DTKDatatypeType>();
			t->symbolID = rawToken.at("symbolID").get<uint64_t>();
		}

		return tokenStream;
	}

	//defines a single line expresstion
	struct LexedSingleLineExpresstion
	{
		std::vector<Token> tokens;
	};

	//defines a lexed file
	struct LexedFile
	{
		std::vector<LexedSingleLineExpresstion> singleLineExpesstions; //the entire file split into new lines

		//generate a debug output file of all the tokens
		inline void GenerateDebugOutputFileOfTokens(const std::string& filepath)
		{
			std::string data = "";
			for (size_t i = 0; i < singleLineExpesstions.size(); ++i)
			{
				for (size_t t = 0; t < singleLineExpesstions[i].tokens.size(); ++t)
				{
				//	//if it's the start of a function
				//	if (singleLineExpesstions[i].tokens[t].type == TokenType::Keyword && singleLineExpesstions[i].tokens[t].specificType == SpecificTokenType::Keyword_FuncStart)
				//		data += "func ";

				//	else //if it's the start of a function
				//		if (singleLineExpesstions[i].tokens[t].type == TokenType::Keyword && singleLineExpesstions[i].tokens[t].specificType == SpecificTokenType::Keyword_ObjStart)
				//			data += "struct ";

				//	//if it's the end of a function or object
				//	else if (singleLineExpesstions[i].tokens[t].type == TokenType::Keyword && singleLineExpesstions[i].tokens[t].specificType == SpecificTokenType::Keyword_FuncEnd ||
				//		singleLineExpesstions[i].tokens[t].type == TokenType::Keyword && singleLineExpesstions[i].tokens[t].specificType == SpecificTokenType::Keyword_ObjEnd)
				//		data += "};";

					////if it's a jump label
					//else if (singleLineExpesstions[i].tokens[t].type == TokenType::JumpLabelDefinition)
					//{
					//	data += "Jump Label (" + singleLineExpesstions[i].tokens[t].data + "):";
					//}

					//otherwise
					/*else
					{
						data += singleLineExpesstions[i].tokens[t].data;

						data += ' ';
					}*/
				}
				data += '\n';
			}

			std::fstream f(filepath, std::ios::out);
			f.write(data.c_str(), data.size());
		}
	};
}