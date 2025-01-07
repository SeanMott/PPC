#include <PPC/Stage2/IR.hpp>

//takes a serious of line expresstions and passes them through Subpass 1
static inline std::vector<PPC::Stage2::Node> Subpass1_FunctionAndStructBoundChecking(const std::vector<PPC::Stage1::LexedSingleLineExpresstion>& lineExpresstions)
{
	std::vector<PPC::Stage2::Node> nodes;
	const size_t lineCount = lineExpresstions.size();
	nodes.reserve(lineCount / 2);
	for (size_t l = 0; l < lineCount; ++l)
	{
		//strips the line expresstion if it's a hidden
		if (lineExpresstions[l].tokens[0].type == PPC::Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_Scope_Hidden)
			continue;

		//if it's a .sym
		else if (lineExpresstions[l].tokens[0].type == PPC::Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_Scope_Sym)
		{
			PPC::Stage2::Node node;

			node.type = PPC::Stage2::NodeType::SysAddressDef;

			//gets name
			node.symLabelDef.name = lineExpresstions[l].tokens[1].data;

			//skips the comma

			//gets the scope
			//node->functionHeaderDef.scope = lineExpresstions[l].tokens[3].data;
			node.symLabelDef.scope = PPC::Data::ScopeKeyword::Global;

			nodes.emplace_back(node);
		}

		//if it's the start of a function
		else if (lineExpresstions[l].tokens[0].type == PPC::Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_FuncStart)
		{
			PPC::Stage2::Node node;

			node.type = PPC::Stage2::NodeType::FunctionDef;

			//gets name
			node.functionHeaderDef.name = lineExpresstions[l].tokens[1].data;

			//skips the comma

			//gets the scope
			//node->functionHeaderDef.scope = lineExpresstions[l].tokens[3].data;
			node.functionHeaderDef.scope = PPC::Data::ScopeKeyword::Global;

			nodes.emplace_back(node);
		}

		//if it's the end of a function
		else if (lineExpresstions[l].tokens[0].type == PPC::Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_FuncEnd)
		{
			PPC::Stage2::Node node;
			node.type = PPC::Stage2::NodeType::FunctionDefEnd;
			nodes.emplace_back(node);
		}

		//if it's the start of a struct
		else if (lineExpresstions[l].tokens[0].type == PPC::Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_ObjStart)
		{
			PPC::Stage2::Node node;

			node.type = PPC::Stage2::NodeType::StructDef;

			//gets name
			node.structHeaderDef.name = lineExpresstions[l].tokens[1].data;

			//skips the comma

			//gets the scope
			//node->structHeaderDef.scope = lineExpresstions[l].tokens[3].data;
			node.structHeaderDef.scope = PPC::Data::ScopeKeyword::Global;

			nodes.emplace_back(node);
		}

		//if it's the end of a function
		else if (lineExpresstions[l].tokens[0].type == PPC::Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_ObjEnd)
		{
			PPC::Stage2::Node node;
			node.type = PPC::Stage2::NodeType::StructDefEnd;
			nodes.emplace_back(node);
		}

		//if it's a jump label
		else if (lineExpresstions[l].tokens[0].type == PPC::Stage1::TokenType::JumpLabelDefinition)
		{
			PPC::Stage2::Node node;
			node.type = PPC::Stage2::NodeType::JumpLabelDef;
			node.jumpLabelDef.name = lineExpresstions[l].tokens[0].data;
			nodes.emplace_back(node);
		}

		//if it's something we can't parse
		else
		{
			PPC::Stage2::Node n;
			n.type = PPC::Stage2::NodeType::Unknown;
			n.lineExpresstion = lineExpresstions[l];
			nodes.emplace_back(n);
		}
	}

	return nodes;
}

//second passes generates metadata for instructions and their parameters and variables in structs
static inline void Subpass2_StructVarsAndInstructions(std::vector<PPC::Stage2::Node>& nodes)
{
	//goes through the nodes and checks for instructions, generating the broad expresstion types
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		//if it's unknown, we parse it furthur
		if (nodes[i].type == PPC::Stage2::NodeType::Unknown)
		{
			//if instruction
			if (nodes[i].lineExpresstion.tokens[0].type == PPC::Stage1::TokenType::Instruction)
			{
				nodes[i].type = PPC::Stage2::NodeType::Instruction_Expresstion;

				//generate the first instruction Node
				nodes[i].instruction.instruction = nodes[i].lineExpresstion.tokens[0];

				//generates the paramter nodes
				PPC::Stage2::InstructionParameter* param = nullptr;
				const size_t paramCount = nodes[i].lineExpresstion.tokens.size();

				if (paramCount > 0)
				{
					param = &nodes[i].instruction.parameters.emplace_back(PPC::Stage2::InstructionParameter());
					for (size_t p = 1; p < paramCount; ++p)
					{
						//if it's a comma, this is the start of a new parameter
						if (nodes[i].lineExpresstion.tokens[p].type == PPC::Stage1::TokenType::Operator && nodes[i].lineExpresstion.tokens[p].data == ",")
							param = &nodes[i].instruction.parameters.emplace_back(PPC::Stage2::InstructionParameter());

						//otherwise add it to the current one
						else
							param->options.emplace_back(PPC::Stage2::NodeOrTokenOption()).token = nodes[i].lineExpresstion.tokens[p];
					}
				}

			}

			//if datatype
			else if (nodes[i].lineExpresstion.tokens[0].type == PPC::Stage1::TokenType::Datatype)
			{
				nodes[i].type = PPC::Stage2::NodeType::Datatype_Exprestion;

				//generate the first datatype Node
				nodes[i].variable.datatype = nodes[i].lineExpresstion.tokens[0];

				//generates the value paramter nodes
				PPC::Stage2::VariableValueParameter* param = nullptr;
				const size_t paramCount = nodes[i].lineExpresstion.tokens.size();

				if (paramCount > 0)
				{
					param = &nodes[i].variable.parameters.emplace_back(PPC::Stage2::VariableValueParameter());
					for (size_t p = 1; p < paramCount; ++p)
					{
						//if it's a comma, this is the start of a new parameter
						if (nodes[i].lineExpresstion.tokens[p].type == PPC::Stage1::TokenType::Operator && nodes[i].lineExpresstion.tokens[p].data == ",")
							param = &nodes[i].variable.parameters.emplace_back(PPC::Stage2::VariableValueParameter());

						//otherwise add it to the current one
						else
							param->options.emplace_back(PPC::Stage2::NodeOrTokenOption()).token = nodes[i].lineExpresstion.tokens[p];
					}
				}
			}
		}
	}
}

//furthur define the instruction parameters, resolving memory offsets
static inline void Subpass3_ResolveInstructionParamHighLowMemoryOffsets(std::vector<PPC::Stage2::Node>& nodes)
{
	//furthur refine the instructions memory offset parameters
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		//get the instruction
		if (nodes[i].type == PPC::Stage2::NodeType::Instruction_Expresstion)
		{
			//goes through the paremeters and check for a memory offset
			for (size_t p = 0; p < nodes[i].instruction.parameters.size(); ++p)
			{
				PPC::Stage2::InstructionParameter* param = &nodes[i].instruction.parameters[p];
				const size_t tokenCount = param->options.size();
				if (tokenCount < 3) //if there's not enough tokens for the generation
					continue;

				//if we have a @ this is a memory offset

				//if we have a sda21

				//if we have a low bit

				//if we have a high bit

				//compress the () offsets
			}
		}
	}
}

//parses the expresstions into Node IR
std::vector<PPC::Stage2::Node> PPC::Stage2::ParseExpresstionsIntoNodeIR(const std::vector<Stage1::LexedSingleLineExpresstion>& lineExpresstions)
{
	//generate inital structs and functions
	std::vector<PPC::Stage2::Node> nodes = Subpass1_FunctionAndStructBoundChecking(lineExpresstions);
	
	//generate instructions and variabes
	Subpass2_StructVarsAndInstructions(nodes);
	
	//furthur define the instruction parameters, resolving memory offsets
	Subpass3_ResolveInstructionParamHighLowMemoryOffsets(nodes);

	return nodes;
}