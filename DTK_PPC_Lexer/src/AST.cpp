#include <DTK_PPC_Lexer/AST.hpp>

//processes a stream of tokens into a struct
static inline PPC::Frontend::DTK::ASTNode GenerateASTNode_Struct(const std::vector<PPC::Frontend::DTK::Token>& tokens, const size_t& tokenCount,
	size_t& t, const std::vector<PPC::Frontend::DTK::Symbol::Symbol>& symbols)
{
	PPC::Frontend::DTK::ASTNode structNode;
	structNode.type = PPC::Frontend::DTK::ASTNodeType::Struct;

	//sets the name
	t++;
	structNode.structMetadata.structName = tokens[t].data;
	structNode.structMetadata.nameWasInAString = (tokens[t].type == PPC::Frontend::DTK::TokenType::Literal_String ? true : false); //sets if it was found in strings or not

	//skips the comma
	t++;

	//gets it's scope
	t++;
	structNode.structMetadata.scope = tokens[t].scope;

	//skip the new line
	t++;

	//checks if it's hidden
	t++;
	if (tokens[t].type == PPC::Frontend::DTK::TokenType::DotDirective_Keyword && tokens[t].dotDirective == PPC::Decoder::DotDirectives::DotDirective_Keyword::Hidden)
	{
		structNode.structMetadata.isHidden = true;
		
		//skip till a new line
		while (tokens[t].type != PPC::Frontend::DTK::TokenType::Newline)
		{
			t++;
		}
		t++;
	}

	//parse the variables inside
	while (!(tokens[t].type == PPC::Frontend::DTK::TokenType::DotDirective_Keyword &&
		tokens[t].dotDirective == PPC::Decoder::DotDirectives::DotDirective_Keyword::ObjectEnd))
	{
		PPC::Frontend::DTK::ASTNodeMetadat_Var var;
		var.datatype = tokens[t].datatype; //gets datatype
		t++;

		//goes until the new line
		while (tokens[t].type != PPC::Frontend::DTK::TokenType::Newline)
		{
			var.valueTokens.emplace_back(tokens[t]); //add token
			t++; //increment
		}

		//access what the type is
		if (var.valueTokens.size() > 1)
		{
			var.isValueTokensSeveralTokens = true;

			//checks if it contains a function, label, or struct
			for (size_t vt = 0; vt < var.valueTokens.size(); ++vt)
			{
				if (var.valueTokens[vt].type != PPC::Frontend::DTK::TokenType::Identifier &&
					var.valueTokens[vt].type != PPC::Frontend::DTK::TokenType::Literal_String)
					continue;

				const char* maybeFuncName = var.valueTokens[vt].data.c_str();
				for (size_t s = 0; s < symbols.size(); ++s)
				{
					if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Function)
					{
						var.valueTokensContainsAFucntion = true;
						break;
					}

					if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Object)
					{
						var.valueTokensContainsAStruct = true;
						break;
					}

					if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Label)
					{
						var.valueTokensContainsALabel = true;
						break;
					}
				}
			}
		}
		else if(var.valueTokens.size() > 0)
		{
			if (var.valueTokens[0].type == PPC::Frontend::DTK::TokenType::Identifier)
			{
				var.isValueTokensAIdentifier = true;
			
				//checks if it contains a function, label, or struct and change the datatype to match
				const char* maybeFuncName = var.valueTokens[0].data.c_str();
				for (size_t s = 0; s < symbols.size(); ++s)
				{
					if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Function)
					{
						var.valueTokensContainsAFucntion = true;
						var.datatype = PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte4_FunctionPtr;
						break;
					}

					if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Object)
					{
						var.valueTokensContainsAStruct = true;
						var.datatype = PPC::Decoder::DotDirectives::DotDirective_Datatype::Byte4_Struct;
						break;
					}

					if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Label)
					{
						var.valueTokensContainsALabel = true;
						break;
					}
				}
			}
			else if (var.valueTokens[0].type == PPC::Frontend::DTK::TokenType::Literal_Hex || var.valueTokens[0].type == PPC::Frontend::DTK::TokenType::Literal_Integer ||
				var.valueTokens[0].type == PPC::Frontend::DTK::TokenType::Literal_Float || var.valueTokens[0].type == PPC::Frontend::DTK::TokenType::Literal_String)
			{
				var.isValueTokensALiteral = true;
			
				//checks if it contains a function, label, or struct
				if (var.valueTokens[0].type == PPC::Frontend::DTK::TokenType::Literal_String)
				{
					const char* maybeFuncName = var.valueTokens[0].data.c_str();
					for (size_t s = 0; s < symbols.size(); ++s)
					{
						if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Function)
						{
							var.valueTokensContainsAFucntion = true;
							break;
						}

						if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Object)
						{
							var.valueTokensContainsAStruct = true;
							break;
						}

						if (!strcmp(symbols[s].name.c_str(), maybeFuncName) && symbols[s].type == PPC::Frontend::DTK::Symbol::SymbolType::Label)
						{
							var.valueTokensContainsALabel = true;
							break;
						}
					}
				}
			}
		}

		//adds var
		structNode.structMetadata.variables.emplace_back(var);

		t++; //increment loop
	}

	return structNode;
}

std::vector<PPC::Frontend::DTK::ASTNode> PPC::Frontend::DTK::GenerateAST(const std::vector<PPC::Frontend::DTK::Token>& tokens,
	const std::vector<Symbol::Symbol>& symbols)
{
	const size_t tokenCount = tokens.size();

	std::vector<PPC::Frontend::DTK::ASTNode> tree; tree.reserve(tokenCount / 2);

	for (size_t t = 0; t < tokenCount; ++t)
	{
		//if it's the start of a object
		if (tokens[t].type == PPC::Frontend::DTK::TokenType::DotDirective_Keyword &&
			tokens[t].dotDirective == PPC::Decoder::DotDirectives::DotDirective_Keyword::ObjectStart)
			tree.emplace_back(GenerateASTNode_Struct(tokens, tokenCount, t, symbols));

		//parses a function
	}

	return tree;
}