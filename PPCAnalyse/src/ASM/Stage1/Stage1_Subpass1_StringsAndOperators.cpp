#include <PPCAnalyse/ASM/Stage1/Stage1_Subpass1_StringsAndOperators.hpp>

#include <PPCLib/Data/Operators.hpp>

//makes a comment block token
static inline PPC::Token::Token MakeToken_CommentBlock(const std::string& code, const size_t& codeLength, size_t& sourceIndex)
{
	PPC::Token::Token t;
	t.type = PPC::Token::TokenType::BlockComment;

	//skips the current char since it's the *
	sourceIndex++;

	//parses the string
	while (sourceIndex < codeLength)
	{
		//if it's the end
		if (sourceIndex + 1 < codeLength && code[sourceIndex] == '*' && code[sourceIndex + 1] == '/')
			break;

		//add char
		t.data += code[sourceIndex];
		sourceIndex++;
	}
	sourceIndex++;

	return t;
}

//makes a string literal token
static inline PPC::Token::Token MakeToken_StringLiteral(const std::string& code, const size_t& codeLength, size_t& sourceIndex)
{
	PPC::Token::Token t;
	t.type = PPC::Token::TokenType::Literal_String;

	//skips the current char since it's the "
	sourceIndex++;

	//parses the string
	while (sourceIndex < codeLength)
	{
		//if it's the end
		if (sourceIndex > 0 && code[sourceIndex - 1] != '\\' && code[sourceIndex] == '"')
			break;

		//add char
		t.data += code[sourceIndex];
		sourceIndex++;
	}
	sourceIndex++;

	return t;
}

//makes a operator token
static inline PPC::Token::Token MakeToken_Operator(const char& op)
{
	PPC::Token::Token t;
	t.type = PPC::Token::TokenType::Operator;
	t.data = std::string((&op));
	return t;
}

//makes a new line token
static inline PPC::Token::Token MakeToken_NewLine()
{
	PPC::Token::Token t;
	t.type = PPC::Token::TokenType::NewLine;
	t.data = "\n";
	return t;
}

//makes a genaric token
static inline PPC::Token::Token MakeToken_Genaric(const std::string& word)
{
	PPC::Token::Token t;
	t.type = PPC::Token::TokenType::Genaric;
	t.data = word;
	return t;
}

//parses the subpass
std::vector<PPC::Token::Token> PPC::Analyse::ASM::Stage1::Subpass::PerformSubpass1(const std::string& code)
{
	std::vector<Token::Token> tokens; tokens.reserve(25);
	const size_t codeLength = code.size();

	std::string word = "";
	for (size_t c = 0; c < codeLength; ++c)
	{
		//if new line
		if (code[c] == '\n')
		{
			if (word != "")
			{
				tokens.emplace_back(MakeToken_Genaric(word));
				word = "";
			}
			tokens.emplace_back(MakeToken_NewLine());
			//continue;
		}

		//if space
		else if (code[c] == ' ')
		{
			if (word != "")
			{
				tokens.emplace_back(MakeToken_Genaric(word));
				word = "";
			}
			//continue;
		}

		//if we are starting a string literal
		else if (code[c] == '"')
		{
			if (word != "")
			{
				tokens.emplace_back(MakeToken_Genaric(word));
				word = "";
			}
			tokens.emplace_back(MakeToken_StringLiteral(code, codeLength, c));
			//continue;
		}

		//if it's a operator
		else if (Subpass1_IsOperator(code[c]))
		{
			if (word != "")
			{
				tokens.emplace_back(MakeToken_Genaric(word));
				word = "";
			}
			tokens.emplace_back(MakeToken_Operator(code[c]));
			//continue;
		}

		//processes comment
		else if (c + 1 < codeLength && code[c] == '/' && code[c + 1] == '*')
		{
			c++;
			if (word != "")
			{
				tokens.emplace_back(MakeToken_Genaric(word));
				word = "";
			}
			tokens.emplace_back(MakeToken_CommentBlock(code, codeLength, c));
		}

		//adds to the word
		else
			word += code[c];
	}

	//stores the last bit of word data
	if (word != "")
	{
		tokens.emplace_back(MakeToken_Genaric(word));
		word = "";
	}

	return tokens;
}