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


//parses the expresstions into Node IR
std::vector<PPC::Stage2::Node> PPC::Stage2::ParseExpresstionsIntoNodeIR(const std::vector<Stage1::LexedSingleLineExpresstion>& lineExpresstions)
{
	std::vector<PPC::Stage2::Node> nodes = Subpass1_FunctionAndStructBoundChecking(lineExpresstions);

	//goes through the nodes and checks for instructions, generating the broad expresstion types
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		//if it's unknown, we parse it furthur
		if (nodes[i].type == NodeType::Unknown)
		{
			//if instruction
			if (nodes[i].lineExpresstion.tokens[0].type == Stage1::TokenType::Instruction)
			{
				nodes[i].type = NodeType::Instruction_Expresstion;
			
				//generate the first instruction Node
				nodes[i].instruction.instruction = nodes[i].lineExpresstion.tokens[0];

				//generates the paramter nodes
				InstructionParameter* param = nullptr;
				const size_t paramCount = nodes[i].lineExpresstion.tokens.size();
					
				if (paramCount > 0)
				{
					param = &nodes[i].instruction.parameters.emplace_back(InstructionParameter());
					for (size_t p = 1; p < paramCount; ++p)
					{
						//if it's a comma, this is the start of a new parameter
						if (nodes[i].lineExpresstion.tokens[p].type == Stage1::TokenType::Operator && nodes[i].lineExpresstion.tokens[p].data == ",")
							param = &nodes[i].instruction.parameters.emplace_back(InstructionParameter());

						//otherwise add it to the current one
						else
							param->tokens.emplace_back(nodes[i].lineExpresstion.tokens[p]);
					}
				}
			
			}

			//if datatype
			else if (nodes[i].lineExpresstion.tokens[0].type == Stage1::TokenType::Datatype)
			{
				nodes[i].type = NodeType::Datatype_Exprestion;

				//generate the first datatype Node
				nodes[i].variable.datatype = nodes[i].lineExpresstion.tokens[0];

				//generates the value paramter nodes
				VariableValueParameter* param = nullptr;
				const size_t paramCount = nodes[i].lineExpresstion.tokens.size();

				if (paramCount > 0)
				{
					param = &nodes[i].variable.parameters.emplace_back(VariableValueParameter());
					for (size_t p = 1; p < paramCount; ++p)
					{
						//if it's a comma, this is the start of a new parameter
						if (nodes[i].lineExpresstion.tokens[p].type == Stage1::TokenType::Operator && nodes[i].lineExpresstion.tokens[p].data == ",")
							param = &nodes[i].variable.parameters.emplace_back(VariableValueParameter());

						//otherwise add it to the current one
						else
							param->tokens.emplace_back(nodes[i].lineExpresstion.tokens[p]);
					}
				}
			}
		}
	}

	return nodes;
}