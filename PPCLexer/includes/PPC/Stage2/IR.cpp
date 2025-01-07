#include <PPC/Stage2/IR.hpp>

//


//parses the expresstions into Node IR
std::vector<PPC::Stage2::Node> PPC::Stage2::ParseExpresstionsIntoNodeIR(const std::vector<Stage1::LexedSingleLineExpresstion>& lineExpresstions)
{
	std::vector<PPC::Stage2::Node> nodes;
	const size_t lineCount = lineExpresstions.size();
	nodes.reserve(lineCount / 2);
	for (size_t l = 0; l < lineCount; ++l)
	{
		//if it's the start of a function
		if (lineExpresstions[l].tokens[0].type == Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == Stage1::SpecificTokenType::Keyword_FuncStart)
		{
			Node node;

			node.type = NodeType::FunctionDef;

			//gets name
			node.functionHeaderDef.name = lineExpresstions[l].tokens[1].data;

			//skips the comma

			//gets the scope
			//node->functionHeaderDef.scope = lineExpresstions[l].tokens[3].data;
			node.functionHeaderDef.scope = Data::ScopeKeyword::Global;

			nodes.emplace_back(node);
		}

		//if it's the end of a function
		else if (lineExpresstions[l].tokens[0].type == Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == Stage1::SpecificTokenType::Keyword_FuncEnd)
		{
			Node node;
			node.type = NodeType::FunctionDefEnd;
			nodes.emplace_back(node);
		}

		//if it's the start of a struct
		else if (lineExpresstions[l].tokens[0].type == Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == Stage1::SpecificTokenType::Keyword_ObjStart)
		{
			Node node;

			node.type = NodeType::StructDef;

			//gets name
			node.structHeaderDef.name = lineExpresstions[l].tokens[1].data;

			//skips the comma

			//gets the scope
			//node->structHeaderDef.scope = lineExpresstions[l].tokens[3].data;
			node.structHeaderDef.scope = Data::ScopeKeyword::Global;

			nodes.emplace_back(node);
		}

		//if it's the end of a function
		else if (lineExpresstions[l].tokens[0].type == Stage1::TokenType::Keyword && lineExpresstions[l].tokens[0].specificType == Stage1::SpecificTokenType::Keyword_ObjEnd)
		{
			Node node;
			node.type = NodeType::StructDefEnd;
			nodes.emplace_back(node);
		}

		//if it's something we can't parse
		else
		{
			Node n;
			n.type = NodeType::Unknown;
			n.lineExpresstion.emplace_back(lineExpresstions[l]);
			nodes.emplace_back(n);
		}
	}

	return nodes;
}