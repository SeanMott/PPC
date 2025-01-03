#include <PPC/Stage1/Token.hpp>

//defines a parser
struct Parser
{
	size_t lineCount = 1, charCount = 0,
		codeIndex = 0, codeLength = 0;
	std::string code = "";

	//sets the code
	inline void Parser_SetCodeForParsing(const std::string rawCode)
	{
		code = rawCode;
		codeLength = rawCode.size();
		codeIndex = 0;
		lineCount = 1;
		charCount = 0;
	}

	//gets the next char
	inline char Parser_GetNextChar()
	{
		if (codeIndex + 1 >= codeLength)
			return -1;

		codeIndex++;
		return code[codeIndex];
	}

	//peeks the next char
	inline char Parser_PeekNextChar()
	{
		if (codeIndex + 1 >= codeLength)
			return -1;

		return code[codeIndex + 1];
	}
};

//processes a operator token
static inline PPC::Stage1::Token Subpass1_GenerateToken_Operator(const char data, Parser* parser)
{
	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::Operator;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	//fmt::print("Line: {}, Char: {} || Operator || {}\n", parser->lineCount, parser->charCount, data);
	return t;
}

//processes the # comment
static inline PPC::Stage1::Token Subpass1_GenerateToken_PoundSingleLineComment(Parser* parser)
{
	std::string data = "";

	//goes till the new line
	while (parser->Parser_PeekNextChar() != '\n')
		data += parser->Parser_GetNextChar();

	//fmt::print("Line: {}, Char: {} || Single Line Comment || {}\n", lineCount, charCount, data);

	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::SingleLineComment;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//processes the block comment
static inline PPC::Stage1::Token Subpass1_GenerateToken_BlockLineComment(Parser* parser)
{
	std::string data = "";

	//goes till the end of the block
	parser->Parser_GetNextChar(); //skip the * after the /
	char c = parser->Parser_GetNextChar();
	while (c != -1)
	{
		data += c;
		c = parser->Parser_GetNextChar();
		
		if (c == '*' && parser->Parser_PeekNextChar() == '/')
		{
			c = parser->Parser_GetNextChar(); //skip the /
			break;
		}
	}

	//fmt::print("Line: {}, Char: {} || Block Comment || {}\n", lineCount, charCount, data);
	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::BlockComment;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//processes the string literal
static inline PPC::Stage1::Token Subpass1_GenerateToken_StringLiteral(Parser* parser)
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

	//fmt::print("Line: {}, Char: {} || String Literal || {}\n", parser->lineCount, parser->charCount, data);
	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::Literal_String;
	t.data = data;
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//makes a word
static inline PPC::Stage1::Token Subpass1_GenerateTokenFromWord(std::string& word, Parser* parser)
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

	//fmt::print("Line: {}, Char: {} || {}\n", parser->lineCount, parser->charCount, word);

	t.type = PPC::Stage1::TokenType::Genaric;
	t.data = std::string(word);
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;

	word = "";
	return t;
}

//generates a new line token
static inline PPC::Stage1::Token Subpass1_GenerateToken_NewLine(Parser* parser)
{
	//fmt::print("Line: {}, Char: {} || New Line\n", parser->lineCount, parser->charCount);

	PPC::Stage1::Token t;
	t.type = PPC::Stage1::TokenType::NewLine;
	t.data = "";
	t.lineCount = parser->lineCount;
	t.charCount = parser->charCount;
	return t;
}

//list all operator tokens
#define PPC_LEXER_OPERATOR_COUNT 5
static const char PPC_LEXER_OPERATOR_TOKEN_STRINGS[PPC_LEXER_OPERATOR_COUNT] = { ',', '(', ')', '@', ':' };

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

//lists all the keywords
#define PPC_LEXER_KEYWORDS_COUNT 15
static const char* PPC_LEXER_KEYWORDS_TOKEN_STRINGS[PPC_LEXER_KEYWORDS_COUNT] = {
	".obj", ".endobj",
	".fn", ".endfn",
	"global", "local", "weak",
	".hidden",
	".include", ".file",
	".section", ".init", ".balign",
	".sdata2", "sda21"
};

//checks if it's a keyword
static inline bool Subpass2_IsKeyword(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_KEYWORDS_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_KEYWORDS_TOKEN_STRINGS[i]))
			return true;
	}

	return false;
}

//is it the start of a function def
//static inline bool Subpass2_IsStartOfFuncDef(const char* key) { return (!strcmp(key, PPC_LEXER_KEYWORDS_TOKEN_STRINGS[2]) ? true : false); }

//is it the end of a function def
//static inline bool Subpass2_IsEndOfFuncDef(const char* key) { return (!strcmp(key, PPC_LEXER_KEYWORDS_TOKEN_STRINGS[3]) ? true : false); }

//is it the start of a object def
//static inline bool Subpass2_IsStartOfObjectDef(const char* key) { return (!strcmp(key, PPC_LEXER_KEYWORDS_TOKEN_STRINGS[0]) ? true : false); }

//is it the end of a object def
//static inline bool Subpass2_IsEndOfObjectDef(const char* key) { return (!strcmp(key, PPC_LEXER_KEYWORDS_TOKEN_STRINGS[1]) ? true : false); }

//is it the scope modifier

//lists the datatypes
#define PPC_LEXER_DATATYPE_COUNT 4
static const char* PPC_LEXER_DATATYPE_STRINGS[PPC_LEXER_DATATYPE_COUNT] = {
	".skip", ".4byte", ".double", ".float"
};

//checks if it's a datatype
static inline bool Subpass2_IsDatatype(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_DATATYPE_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_DATATYPE_STRINGS[i]))
			return true;
	}

	return false;
}

//lists the registers
#define PPC_LEXER_INTEGER_REGISTER_COUNT 32
static const char* PPC_LEXER_INTEGER_REGISTER_STRINGS[PPC_LEXER_INTEGER_REGISTER_COUNT] = {
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19",
	"r20", "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"
};

//checks if it's a integer register
static inline bool Subpass2_IsIntegerRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_INTEGER_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_INTEGER_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}

//parses raw code into Genaric Tokens for Subpass 1
//read the Subpass 1: Genaric Token Splits in the README
static inline std::vector<PPC::Stage1::Token> Subpass1_GenerateGeneralTokens(const std::string& rawCode)
{
	Parser parser;
	parser.Parser_SetCodeForParsing(rawCode);
	std::vector<PPC::Stage1::Token> subpass1_Tokens;
	subpass1_Tokens.reserve(20);

	//goes through the code, removing extra spaces and tabs
	std::string word = "";
	char c = parser.code[parser.codeIndex];
	while(c != -1)
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

//processes the subpass 2
static inline std::vector<PPC::Stage1::Token> Subpass2_GenerateTokens(std::vector<PPC::Stage1::Token>& subpass1Tokens)
{
	const size_t subpass1TokenCount = subpass1Tokens.size();
	std::vector<PPC::Stage1::Token> tokens;
	tokens.reserve(subpass1TokenCount);

	//compress the tokens into the new tree
	for (size_t i = 0; i < subpass1TokenCount; ++i)
	{
		//if it's genaric we parse it for furthur data
		if (subpass1Tokens[i].type == PPC::Stage1::TokenType::Genaric)
		{
			//if it's a keyword
			if (Subpass2_IsKeyword(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;

				//specifies the type of keyword
			}

			//if it's a datatype
			else if (Subpass2_IsDatatype(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Datatype;
			}

			//if it's a int register
			else if (Subpass2_IsIntegerRegister(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Int;
			}

			//if it's a digit literal

			//else it's a Identifier
			else
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Identifier;
		}

		//skip the ignore
		else if (subpass1Tokens[i].type == PPC::Stage1::TokenType::Count)
		{
			continue;
		}

		//if we're not ignoring it and after specififying it's type, we toss it in the new tree
		tokens.emplace_back(subpass1Tokens[i]);
	}

	return tokens;
}

//processes the subpass 4
static inline std::vector<PPC::Stage1::Token> Subpass4_GenerateTokens(std::vector<PPC::Stage1::Token>& subpass3Tokens)
{
	const size_t subpass3TokenCount = subpass3Tokens.size();
	std::vector<PPC::Stage1::Token> tokens;
	tokens.reserve(subpass3TokenCount);

	//compress the tokens into the new tree
	for (size_t i = 0; i < subpass3TokenCount; ++i)
	{
		//check for this line and the next few to be invalid structure and skip it all if so
		if (subpass3Tokens[i].type == PPC::Stage1::TokenType::BlockComment && subpass3Tokens[i + 1].type == PPC::Stage1::TokenType::Datatype &&
			subpass3Tokens[i + 2].type == PPC::Stage1::TokenType::Identifier && subpass3Tokens[i + 3].type == PPC::Stage1::TokenType::BlockComment)
		{
			if (subpass3Tokens[i + 3].data == " invalid ")
			{
				i += 4;
				continue;
			}
		}

		tokens.emplace_back(subpass3Tokens[i]);
		subpass3Tokens[i].Print();
	}

	return tokens;
}

//lexes ASM into tokens
std::vector<PPC::Stage1::Token> PPC::Stage1::LexTokens(const Data::TranslationUnit& tu)
{
	//Subpass 1: Genaric Token Splits || read details in the README
	std::vector<PPC::Stage1::Token> subpass1_Tokens = Subpass1_GenerateGeneralTokens(tu.code);

	//Subpass 2:  Keywords and fine typing || read details in the README
	std::vector<PPC::Stage1::Token> subpass2_Tokens = Subpass2_GenerateTokens(subpass1_Tokens);
	subpass1_Tokens.clear(); //we don't need the old tree anymore

	//Subpass 3: Jump Labels and Func/Object Names || read details in the README

	//Subpass 4: Remove Invalid Instructions || read details in the README
	std::vector<PPC::Stage1::Token> subpass4_Tokens = Subpass4_GenerateTokens(subpass2_Tokens);
	subpass2_Tokens.clear();


	return subpass4_Tokens;
}