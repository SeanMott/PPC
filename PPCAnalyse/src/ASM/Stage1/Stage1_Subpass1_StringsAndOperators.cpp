#include <PPCAnalyse/ASM/Stage1/Stage1_Subpass1_StringsAndOperators.hpp>

#include <PPCLib/Data/Operators.hpp>

//makes a string literal token
static inline PPC::Token::Token MakeToken_StringLiteral(const std::string& code, const size_t& codeLength, size_t& sourceIndex)
{
	//skips the current char since it's the "
	sourceIndex++;

	//parses the string
	std::string str = "";
	while (sourceIndex < codeLength)
	{
		//if it's the end
		if (sourceIndex > 0 && code[sourceIndex - 1] != '\\' && code[sourceIndex] == '"')
			break;

		//add char
		str += code[sourceIndex];
		sourceIndex++;
	}

	return {
		0, 0,
		PPC::Token::TokenType::Literal_String,
		PPC::Token::SpecificTokenType::Count,
		{},
		str
	};
}

//makes a operator token
static inline PPC::Token::Token MakeToken_Operator(const char& op)
{
	return {
		0, 0,
		PPC::Token::TokenType::Operator,
		PPC::Token::SpecificTokenType::Count,
		{},
		std::string((&op))
	};
}

//makes a new line token
static inline PPC::Token::Token MakeToken_NewLine()
{
	return {
		0, 0,
		PPC::Token::TokenType::NewLine,
		PPC::Token::SpecificTokenType::Count,
		{},
		"\n"
	};
}

//makes a genaric token
static inline PPC::Token::Token MakeToken_Genaric(const std::string& word)
{
	return {
		0, 0,
		PPC::Token::TokenType::Genaric,
		PPC::Token::SpecificTokenType::Count,
		{},
		word
	};
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
			continue;
		}

		//if space
		else if (code[c] == ' ')
		{
			if (word != "")
			{
				tokens.emplace_back(MakeToken_Genaric(word));
				word = "";
			}
			continue;
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
			continue;
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
			continue;
		}

		//adds to the word
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