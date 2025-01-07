#pragma once

//defines a IR token for storing the data

#include <PPC/Stage1/Token.hpp>

#include <PPC/Data/Scope.hpp>

namespace PPC::Stage2
{
	//defines a Node in the IR
	enum class NodeType
	{
		FunctionDef = 0, //defines the name and scope of a function
		FunctionDefEnd,
		
		StructDef, //defines the name and scope of a struct
		StructDefEnd,

		JumpLabelDef, //defines a jump label
		
		SysAddressDef, //defines a sym address

		Datatype, //defines a datatype expresstion we define inside a struct

		Instruction, //defines a instruction expresstion in a function

		Unknown, //we don't know what this expresstion is, this means it needs debuging.
		//as all unknown sysmbols should have been purged already

		Count
	};

	//defines a function definition header
	struct FunctionHeaderDef
	{
		std::string name = "";
		Data::ScopeKeyword scope = Data::ScopeKeyword::Count;
	};

	//defines a struct definition header
	struct StructHeaderDef
	{
		std::string name = "";
		Data::ScopeKeyword scope = Data::ScopeKeyword::Count;
	};

	//defines a jump label defintion
	struct JumpLabelDef
	{
		std::string labelName = ""; //the name of this label
		std::string ownerName = ""; //what function or struct owns this label
	};

	//defines a sym jump label
	struct SymJumpLabelDef
	{
		std::string name = "";
		Data::ScopeKeyword scope = Data::ScopeKeyword::Count;
	};

	//defines a general Node
	struct Node
	{
		NodeType type = NodeType::Count;
		std::vector<Stage1::LexedSingleLineExpresstion> lineExpresstion; //defines the general like expresstion

		//the specific bits of node data
		FunctionHeaderDef functionHeaderDef;
		StructHeaderDef structHeaderDef;
		JumpLabelDef jumpLabelDef;
		SymJumpLabelDef symLabelDef;

		//generates debug IR text
		inline std::string GenerateDebugIR() const
		{
			std::string IR = "";

			switch (type)
			{
			case NodeType::FunctionDef:
				IR += "static inline void " + functionHeaderDef.name + "(PPCRuntime::Context* context)\n{\n";
				return IR;

			case NodeType::FunctionDefEnd:
				IR += "\n}\n";
				return IR;

			case NodeType::StructDef:
				IR += "struct " + structHeaderDef.name + "\n{\n";
				return IR;

			case NodeType::StructDefEnd:
				IR += "\n};\n";
				return IR;

			case NodeType::SysAddressDef:
				IR += "Sym Address Jump || Static || " + symLabelDef.name + "\n";
				return IR;

			case NodeType::Unknown:
				IR = "/*unable to parse the following Token Line Expresstion to IR. If it is a missing instruction make a pull on the github.";

				for (size_t i = 0; i < lineExpresstion.size(); ++i)
				{
					IR += "\n//";
					for (size_t t = 0; t < lineExpresstion[i].tokens.size(); ++t)
					{
						IR += ' ';
						IR += (lineExpresstion[i].tokens[t].type == Stage1::TokenType::Literal_String ? "\"" + lineExpresstion[i].tokens[t].data + "\"" : lineExpresstion[i].tokens[t].data);
					}
				}
				IR += "\n*/\n";

				return IR;
			}

			return "";
		}
	};

	//parses the expresstions into Node IR
	std::vector<Node> ParseExpresstionsIntoNodeIR(const std::vector<Stage1::LexedSingleLineExpresstion>& lineExpresstions);
}