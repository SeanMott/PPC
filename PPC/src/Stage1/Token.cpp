#include <PPC/Stage1/Token.hpp>

size_t lineCount = 1, charCount = 0,
codeIndex = 0, codeLength = 0;
std::string code = "";

//sets the code
static inline void Parser_SetCodeForParsing(const std::string rawCode)
{
	code = rawCode;
	codeLength = rawCode.size();
	codeIndex = 0;
	lineCount = 1;
	charCount = 0;
}

//gets the next char
static inline char Parser_GetNextChar()
{
	if (codeIndex + 1 >= codeLength)
		return -1;

	codeIndex++;
	return code[codeIndex];
}

//peeks the next char
static inline char Parser_PeekNextChar()
{
	if (codeIndex + 1 >= codeLength)
		return -1;

	return code[codeIndex + 1];
}

//list all operator tokens
#define PPC_LEXER_OPERATOR_COUNT 4
static const char PPC_LEXER_OPERATOR_TOKEN_STRINGS[PPC_LEXER_OPERATOR_COUNT] = { ',', '(', ')', '@'};

//checks if it's a operator
static inline bool Subpass1_IsOperator(const char op)
{
	for (size_t i = 0; i < PPC_LEXER_OPERATOR_COUNT; ++i)
	{
		if (op == PPC_LEXER_OPERATOR_TOKEN_STRINGS[i])
			return true;
	}

	return false;
}

//processes a operator token
static inline void Subpass1_GenerateToken_Operator(const char data)
{
	fmt::print("Line: {}, Char: {} || Operator || {}\n", lineCount, charCount, data);
}

//processes the # comment
static inline void Subpass1_GenerateToken_PoundSingleLineComment()
{
	std::string data = "";

	//goes till the new line
	while (Parser_PeekNextChar() != '\n')
		data += Parser_GetNextChar();

	//fmt::print("Line: {}, Char: {} || Single Line Comment || {}\n", lineCount, charCount, data);
}

//processes the block comment
static inline void Subpass1_GenerateToken_BlockLineComment()
{
	std::string data = "";

	//goes till the end of the block
	Parser_GetNextChar(); //skip the * after the /
	char c = Parser_GetNextChar();
	while (c != -1)
	{
		data += c;
		c = Parser_GetNextChar();
		
		if (c == '*' && Parser_PeekNextChar() == '/')
			break;
	}
	c = Parser_GetNextChar();

	//fmt::print("Line: {}, Char: {} || Block Comment || {}\n", lineCount, charCount, data);
}

//makes a word
static inline void Subpass1_GenerateTokenFromWord(std::string& word)
{
	fmt::print("Line: {}, Char: {} || {}\n", lineCount, charCount, word);
	word = "";
}

//parses raw code into Genaric Tokens for Subpass 1
//read the Subpass 1: Genaric Token Splits in the README
static inline std::vector<PPC::Stage1::Token> Subpass1_GenerateGeneralTokens(const std::string& rawCode)
{
	Parser_SetCodeForParsing(rawCode);
	std::vector<PPC::Stage1::Token> subpass1_Tokens;
	subpass1_Tokens.reserve(20);

	//goes through the code, removing extra spaces and tabs
	std::string word = "";
	char c = code[codeIndex];
	while(c != -1)
	{
		//if new line
		if (c == '\n')
		{
			Subpass1_GenerateTokenFromWord(word);
			lineCount++;
		}

		//if space or tab or new line
		else if (c == ' ' || c == '\t' || c == '\n')
			Subpass1_GenerateTokenFromWord(word);

		//if string literal

		//if operator
		else if (Subpass1_IsOperator(c))
		{
			Subpass1_GenerateTokenFromWord(word);
			Subpass1_GenerateToken_Operator(c);
		}

		//if # comment
		else if (c == '#')
		{
			Subpass1_GenerateTokenFromWord(word);
			Subpass1_GenerateToken_PoundSingleLineComment();
		}

		//if block comment
		else if (c == '/' && Parser_PeekNextChar() == '*')
		{
			Subpass1_GenerateTokenFromWord(word);
			Subpass1_GenerateToken_BlockLineComment();
		}

		//else if build the word
		else
			word += c;

		//gets the next char
		c = Parser_GetNextChar();
	}

	return subpass1_Tokens;
}

//lexes ASM into tokens
std::vector<PPC::Stage1::Token> PPC::Stage1::LexTokens(const Data::TranslationUnit& tu)
{
	//Subpass 1: Genaric Token Splits || read details in the README
	std::vector<PPC::Stage1::Token> subpass1_Tokens = Subpass1_GenerateGeneralTokens(tu.code);

	std::vector<PPC::Stage1::Token> tokens;

	return tokens;
}