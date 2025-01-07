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

	//defines a instruction parameter type
	enum class InstructionParameterType
	{
		Count
	};

	//defines a instruction parameter node
	struct InstructionParameter
	{
		InstructionParameterType paramterType = InstructionParameterType::Count;
		std::vector<Stage1::Token> tokens;
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
		InstructionParameterType paramterType = InstructionParameterType::Count;
		std::vector<Stage1::Token> tokens;
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
					for (size_t d = 0; d < instruction.parameters[p].tokens.size(); ++d)
					{
						IR += instruction.parameters[p].tokens[d].data;
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
					for (size_t d = 0; d < variable.parameters[p].tokens.size(); ++d)
					{
						IR += variable.parameters[p].tokens[d].data;
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