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

	//defines a general Node
	struct Node
	{
		NodeType type = NodeType::Count;
		std::vector<Stage1::LexedSingleLineExpresstion> lineExpresstion; //defines the general like expresstion

		//the specific bits of node data
		FunctionHeaderDef functionHeaderDef;
		StructHeaderDef structHeaderDef;
		JumpLabelDef jumpLabelDef;

		//prints the node type
		inline void Print() const
		{
			switch (type)
			{
				case NodeType::FunctionDef:
					fmt::print("----Func || Global || {} \n", functionHeaderDef.name.c_str());
					break;

				case NodeType::FunctionDefEnd:
					fmt::print("----Func End \n");
					break;

				case NodeType::StructDef:
					fmt::print("----Struct || Global || {} \n", structHeaderDef.name.c_str());
					break;

				case NodeType::StructDefEnd:
					fmt::print("----Struct End \n");
					break;

				case NodeType::Unknown:
					fmt::print("Unknown: \n");
					break;
			}
		}
	};

	//parses the expresstions into Node IR
	std::vector<Node> ParseExpresstionsIntoNodeIR(const std::vector<Stage1::LexedSingleLineExpresstion>& lineExpresstions);
}