#include <PPCLexer/Subpasses/Subpass1.hpp>

#include <PPCLib/Data/Operators.hpp>

//processes a operator token
static inline PPC::Stage1::Token Subpass1_GenerateToken_Operator(const char data, PPC::Stage1::Parser* parser)
{
	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::Operator;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//processes the # comment
static inline PPC::Stage1::Token Subpass1_GenerateToken_PoundSingleLineComment(PPC::Stage1::Parser* parser)
{
	std::string data = "";

	//goes till the new line
	while (parser->Parser_PeekNextChar() != '\n')
		data += parser->Parser_GetNextChar();

	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::SingleLineComment;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//processes the block comment
static inline PPC::Stage1::Token Subpass1_GenerateToken_BlockLineComment(PPC::Stage1::Parser* parser)
{
	std::string data = "";

	//goes till the end of the block
	parser->Parser_GetNextChar(); //skip the * after the /
	char c = parser->Parser_GetNextChar();
	while (c != -1)
	{
		data += c;
		c = parser->Parser_GetNextChar();

		//if new line, increment the new line
		if (c == '\n')
		{
			parser->lineCount++;
			continue;
		}

		if (c == '*' && parser->Parser_PeekNextChar() == '/')
		{
			c = parser->Parser_GetNextChar(); //skip the /
			break;
		}
	}

	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::BlockComment;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//processes the string literal
static inline PPC::Stage1::Token Subpass1_GenerateToken_StringLiteral(PPC::Stage1::Parser* parser)
{
	std::string data = "";

	//goes till the end of the string
	char c = parser->Parser_GetNextChar();
	while (c != -1)
	{
		data += c;
		c = parser->Parser_GetNextChar();

		//if the next char is the "
		if (c != '\\' && parser->Parser_PeekNextChar() == '"')
		{
			data += c; //gets the last token of the string
			parser->Parser_GetNextChar(); //skip the "
			break;
		}

		//if the current char is the "
		if (c == '"')
			break;
	}

	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::Literal_String;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}



//makes a word
static inline PPC::Stage1::Token Subpass1_GenerateTokenFromWord(std::string& word, PPC::Stage1::Parser* parser)
{
	PPC::Stage1::Token t;

	//if we are going to ignore it
	if (word == "")
	{
		t.type = PPC::Stage1::TokenType::Count;
		t.data = "";
		t.lineCount = parser->lineCount;
		t.charCount = parser->charCount;
		return t;
	}

	//genaric token
	t.type = PPC::Stage1::TokenType::Genaric;
	t.data = std::string(word);
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;

	//we check for extra token specifics so we can multithread it
	if (PPC::Data::ObjectType::IsASMObjectKeyword(t.data.c_str(), t.objType))
		t.type = PPC::Stage1::TokenType::Keyword_Object;

	word = "";
	return t;
}

//generates a new line token
static inline PPC::Stage1::Token Subpass1_GenerateToken_NewLine(PPC::Stage1::Parser* parser)
{

	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::NewLine;
	t.data = "\n";
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//parses raw code into Genaric Tokens for Subpass 1
//read the Subpass 1: Genaric Token Splits in the README
std::vector<PPC::Stage1::Token> PPC::Stage1::Subpass1_GenerateGeneralTokens(const std::string& rawCode)
{
	Parser parser;
	parser.Parser_SetCodeForParsing(rawCode);
	std::vector<PPC::Stage1::Token> subpass1_Tokens;
	subpass1_Tokens.reserve(20);

	//goes through the code, removing extra spaces and tabs
	std::string word = "";
	char c = parser.code[parser.codeIndex];
	while (c != -1)
	{
		//if new line
		if (c == '\n')
		{
			subpass1_Tokens.emplace_back(Subpass1_GenerateTokenFromWord(word, &parser));
			subpass1_Tokens.emplace_back(Subpass1_GenerateToken_NewLine(&parser));
			parser.lineCount++;
		}

		//if space or tab or new line
		else if (c == ' ' || c == '\t' || c == '\n')
			subpass1_Tokens.emplace_back(Subpass1_GenerateTokenFromWord(word, &parser));

		//if string literal
		else if (c == '"')
		{
			subpass1_Tokens.emplace_back(Subpass1_GenerateTokenFromWord(word, &parser));
			subpass1_Tokens.emplace_back(Subpass1_GenerateToken_StringLiteral(&parser));
		}

		//if operator
		else if (Subpass1_IsOperator(c))
		{
			subpass1_Tokens.emplace_back(Subpass1_GenerateTokenFromWord(word, &parser));
			subpass1_Tokens.emplace_back(Subpass1_GenerateToken_Operator(c, &parser));
		}

		//if # comment
		else if (c == '#')
		{
			subpass1_Tokens.emplace_back(Subpass1_GenerateTokenFromWord(word, &parser));
			subpass1_Tokens.emplace_back(Subpass1_GenerateToken_PoundSingleLineComment(&parser));
		}

		//if block comment
		else if (c == '/' && parser.Parser_PeekNextChar() == '*')
		{
			subpass1_Tokens.emplace_back(Subpass1_GenerateTokenFromWord(word, &parser));
			subpass1_Tokens.emplace_back(Subpass1_GenerateToken_BlockLineComment(&parser));
		}

		//else if build the word
		else
			word += c;

		//gets the next char
		c = parser.Parser_GetNextChar();
	}

	return subpass1_Tokens;
}