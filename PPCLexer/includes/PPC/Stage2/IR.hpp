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

		Instruction_Expresstion, //defines a instruction expresstion
		Datatype_Exprestion, //defines a variable definition expresstion

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
		std::string name = ""; //the name of this label
	};

	//defines a sym jump label
	struct SymJumpLabelDef
	{
		std::string name = "";
		Data::ScopeKeyword scope = Data::ScopeKeyword::Count;
	};

	//defines a memory offset ()
	struct NodeParam_MemoryOffset
	{
		std::vector<Stage1::Token> tokens;
	};

	//defines a SDA21
	struct NodeParam_Sda21Invoke
	{

	};

	//defines a high or low bit
	struct NodeParam_LowOrHighBit
	{
		bool isHigh = false;
	};

	//defines a @ for getting a memory offset
	struct NodeParam_GetMemoryOffset
	{

	};

	//defines the state of the option
	enum class NodeOrTokenOptionState
	{
		Token = 0,
		MemoryOffset,
		Sda21,
		LowOrHighBit,
		GetMemoryOffset,

		Count
	};

	//define a duel struct that either contain a Token or a Node
	struct NodeOrTokenOption
	{
		NodeOrTokenOptionState state = NodeOrTokenOptionState::Token;
		Stage1::Token token;
		NodeParam_MemoryOffset memoryOffset;
		NodeParam_Sda21Invoke Sda21;
		NodeParam_LowOrHighBit lowOrHighBit;
		NodeParam_GetMemoryOffset getMemoryOffset;
	};

	//defines a instruction parameter node
	struct InstructionParameter
	{
		//general nodes
		std::vector<NodeOrTokenOption> options;
	};

	//defines a instruction node
	struct Instruction
	{
		Stage1::Token instruction;
		std::vector<InstructionParameter> parameters;
	};

	//defines a variable value parameter node
	struct VariableValueParameter
	{
		std::vector<NodeOrTokenOption> options;
	};

	//defines a variable node
	struct VariableDefinition
	{
		Stage1::Token datatype;
		std::vector<VariableValueParameter> parameters;
	};


	//defines a general Node
	struct Node
	{
		NodeType type = NodeType::Count;
		Stage1::LexedSingleLineExpresstion lineExpresstion; //defines the general like expresstion
		std::vector<Node> nodes; //the internal nodes of this tree

		//the specific bits of node data
		FunctionHeaderDef functionHeaderDef;
		StructHeaderDef structHeaderDef;
		JumpLabelDef jumpLabelDef;
		SymJumpLabelDef symLabelDef;
		Instruction instruction;
		VariableDefinition variable;

		//generates debug IR text
		inline std::string GenerateDebugIR() const
		{
			std::string IR = "";
			size_t paramCount = 0;

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

			case NodeType::JumpLabelDef:
				IR += "Jump Label || " + jumpLabelDef.name + ":\n";
				return IR;

			case NodeType::Instruction_Expresstion:
				IR += "PPC::Runtime::Instructions::" + instruction.instruction.data + "(/* ";

				//adds the parameters
				paramCount = instruction.parameters.size();
				for (size_t p = 0; p < paramCount; ++p)
				{
					for (size_t d = 0; d < instruction.parameters[p].options.size(); ++d)
					{
						if (instruction.parameters[p].options[d].state == NodeOrTokenOptionState::GetMemoryOffset)
							IR += "PPC_RUNTIME_GET_MEMORY_OFFSET_SYMBOL";
						else if (instruction.parameters[p].options[d].state == NodeOrTokenOptionState::LowOrHighBit)
							IR += (instruction.parameters[p].options[d].lowOrHighBit.isHigh == true ? "PPC_RUNTIME_GET_HIGH_BIT" : "PPC_RUNTIME_GET_LOW_BIT");

						else if (instruction.parameters[p].options[d].state == NodeOrTokenOptionState::Sda21)
							IR += "PPC_RUNTIME_SDA21";

						//else if (instruction.parameters[p].options[d].state == NodeOrTokenOptionState::MemoryOffset)
						//{
						//	IR += "PPC_RUNTIME_GET_MEMORY_OFFSET(";
						//	for (size_t t = 0; t < instruction.parameters[p].options[d].memoryOffset.tokens.size(); ++t)
						//	{
						//		IR += instruction.parameters[p].options[d].memoryOffset.tokens[t].data;
						//		IR += (t + 1 < instruction.parameters[p].options[d].memoryOffset.tokens.size() ? " " : "");
						//	}
						//	IR += ")";
						//}


						//if we're printing a token
						else
							IR += instruction.parameters[p].options[d].token.data;
						
						IR += ' ';
					}

					if(p + 1 < paramCount)
						IR += ", ";
				}
				IR += "*/);\n";

				return IR;

			case NodeType::Datatype_Exprestion:
				IR += variable.datatype.data + " <unqiueStructVariableIdentifierNameHere> = ";

				//adds the parameters
				paramCount = variable.parameters.size();
				for (size_t p = 0; p < paramCount; ++p)
				{
					for (size_t d = 0; d < variable.parameters[p].options.size(); ++d)
					{
						//if it's anything
						IR += variable.parameters[p].options[d].token.data;
						
						IR += ' ';
					}

					if (p + 1 < paramCount)
						IR += ", ";
				}
				IR += ";\n";

				return IR;

			case NodeType::Unknown:
				IR = "/*unable to parse the following Token Line Expresstion to IR. If it is a missing instruction make a pull on the github.\n//";
				for (size_t t = 0; t < lineExpresstion.tokens.size(); ++t)
				{
					IR += ' ';
					IR += (lineExpresstion.tokens[t].type == Stage1::TokenType::Literal_String ? "\"" + lineExpresstion.tokens[t].data + "\"" : lineExpresstion.tokens[t].data);
				}
				IR += "\n*/\n";

				return IR;
			}

			return "HEY THIS TYPE OF IR IS NOT HANDLED YET, check that all types are being handled (Type converted to int: " + std::to_string((uint32_t)type) + "\n";
		}
	};

	//parses the expresstions into Node IR
	std::vector<Node> ParseExpresstionsIntoNodeIR(const std::vector<Stage1::LexedSingleLineExpresstion>& lineExpresstions);
}