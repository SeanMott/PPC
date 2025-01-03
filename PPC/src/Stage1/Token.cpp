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
static const char PPC_LEXER_OPERATOR_TOKEN_STRINGS[PPC_LEXER_OPERATOR_COUNT] = { ',', '(', ')', ':', '@'};

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

//is it the start of a function
static inline bool Subpass2_IsKeyword_ObjectDef_Start(const char* key) { return (!strcmp(key, ".obj") ? true : false); }
//is it the end of a function
static inline bool Subpass2_IsKeyword_ObjectDef_End(const char* key) { return (!strcmp(key, ".endobj") ? true : false); }

//is it the start of a object
static inline bool Subpass2_IsKeyword_FunctionDef_Start(const char* key) { return (!strcmp(key, ".fn") ? true : false); }
//is it the end of a object
static inline bool Subpass2_IsKeyword_FunctionDef_End(const char* key) { return (!strcmp(key, ".endfn") ? true : false); }

//is it a alignment keyword
static inline bool Subpass2_IsKeyword_Alignment(const char* key) { return (!strcmp(key, ".balign") ? true : false); }

//is it a scope for global
static inline bool Subpass2_IsKeyword_Scope_Global(const char* key) { return (!strcmp(key, "global") ? true : false); }
//is it a scope for local
static inline bool Subpass2_IsKeyword_Scope_Local(const char* key) { return (!strcmp(key, "local") ? true : false); }
//is it a scope for weak
static inline bool Subpass2_IsKeyword_Scope_Weak(const char* key) { return (!strcmp(key, "weak") ? true : false); }
//is it a scope for hidden
static inline bool Subpass2_IsKeyword_Scope_Hidden(const char* key) { return (!strcmp(key, ".hidden") ? true : false); }
//is it a scope for sys
static inline bool Subpass2_IsKeyword_Scope_Sys(const char* key) { return (!strcmp(key, ".sys") ? true : false); }

//is it a memory offset keyword for sda21
static inline bool Subpass2_IsKeyword_MemoryOffset_Sda21(const char* key) { return (!strcmp(key, "sda21") ? true : false); }
//is it a memory offset keyword for l || lower bit
static inline bool Subpass2_IsKeyword_MemoryOffset_LowerBit(const char* key) { return (!strcmp(key, "l") ? true : false); }
//is it a memory offset keyword for ha || higher bit
static inline bool Subpass2_IsKeyword_MemoryOffset_HigherBit(const char* key) { return (!strcmp(key, "ha") ? true : false); }

//lists the datatypes
#define PPC_LEXER_DATATYPE_COUNT 6
static const char* PPC_LEXER_DATATYPE_STRINGS[PPC_LEXER_DATATYPE_COUNT] = {
	".skip", ".4byte", ".byte", ".double", ".float", ".string"
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

//lists the integer registers
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

//lists the floating registers
#define PPC_LEXER_FLOATING_REGISTER_COUNT 32
static const char* PPC_LEXER_FLOATING_REGISTER_STRINGS[PPC_LEXER_FLOATING_REGISTER_COUNT] = {
	"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19",
	"f20", "f21", "f22", "f23", "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31"
};

//checks if it's a floating register
static inline bool Subpass2_IsFloatingRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_FLOATING_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_FLOATING_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}

//lists the graphics quantized registers
#define PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_COUNT 8
static const char* PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_STRINGS[PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_COUNT] = {
	"qr0", "qr1", "qr2", "qr3", "qr4", "qr5", "qr6", "qr7"
};

//checks if it's a graphics quantized register
static inline bool Subpass2_IsGraphicsQuantizedRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_GRAPHICS_QUANTIZED_REGISTER_STRINGS[i]))
			return true;
	}

	return false;
}

//lists the condition registers
#define PPC_LEXER_CONDITION_REGISTER_COUNT 32
static const char* PPC_LEXER_CONDITION_REGISTER_STRINGS[PPC_LEXER_CONDITION_REGISTER_COUNT] = {
	"cr0lt",
	"cr0gt",
	"cr0eq",
	"cr0un",
	"cr1lt",
	"cr1gt",
	"cr1eq",
	"cr1un",
	"cr2lt",
	"cr2gt",
	"cr2eq",
	"cr2un",
	"cr3lt",
	"cr3gt",
	"cr3eq",
	"cr3un",
	"cr4lt",
	"cr4gt",
	"cr4eq",
	"cr4un",
	"cr5lt",
	"cr5gt",
	"cr5eq",
	"cr5un",
	"cr6lt",
	"cr6gt",
	"cr6eq",
	"cr6un",
	"cr7lt",
	"cr7gt",
	"cr7eq",
	"cr7un"
};

//checks if it's a condition register
static inline bool Subpass2_IsConditionRegister(const char* key)
{
	for (size_t i = 0; i < PPC_LEXER_CONDITION_REGISTER_COUNT; ++i)
	{
		if (!strcmp(key, PPC_LEXER_CONDITION_REGISTER_STRINGS[i]))
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
			//if it's a aligment keyword
			if (Subpass2_IsKeyword_Alignment(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Alignment;
			}

			//if it's a start of a function keyword
			else if (Subpass2_IsKeyword_FunctionDef_Start(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_FuncStart;
			}

			//if it's the end of a function keyword
			else if (Subpass2_IsKeyword_FunctionDef_End(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_FuncEnd;
			}

			//if it's a start of a object keyword
			else if (Subpass2_IsKeyword_ObjectDef_Start(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_ObjStart;
			}

			//if it's the end of a object keyword
			else if (Subpass2_IsKeyword_ObjectDef_End(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_ObjEnd;
			}

			//if it's a global scope keyword
			else if (Subpass2_IsKeyword_Scope_Global(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Global;
			}

			//if it's a local scope keyword
			else if (Subpass2_IsKeyword_Scope_Local(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Local;
			}

			//if it's a weak scope keyword
			else if (Subpass2_IsKeyword_Scope_Weak(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Weak;
			}

			//if it's a hidden scope keyword
			else if (Subpass2_IsKeyword_Scope_Hidden(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Hidden;
			}

			//if it's a sys scope keyword
			else if (Subpass2_IsKeyword_Scope_Sys(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Sys;
			}

			//if it's a sda21 memory offset keyword
			else if (Subpass2_IsKeyword_MemoryOffset_Sda21(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_Sda21;
			}

			//if it's a lower bit memory offset keyword
			else if (Subpass2_IsKeyword_MemoryOffset_LowerBit(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_LowerBit;
			}

			//if it's a higher bit memory offset keyword
			else if (Subpass2_IsKeyword_MemoryOffset_HigherBit(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_HigherBit;
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

			//if it's a floating register
			else if (Subpass2_IsFloatingRegister(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Float;
			}

			//if it's a graphics quantized register
			else if (Subpass2_IsGraphicsQuantizedRegister(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_GraphicsQuantized;
			}

			//if it's a condition register
			else if (Subpass2_IsConditionRegister(subpass1Tokens[i].data.c_str()))
			{
				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Condition;
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

//processes the subpass 3
static inline std::vector<PPC::Stage1::Token> Subpass3_GenerateTokens(std::vector<PPC::Stage1::Token>& subpass2Tokens)
{
	const size_t subpass2TokenCount = subpass2Tokens.size();
	std::vector<PPC::Stage1::Token> tokens;
	tokens.reserve(subpass2TokenCount);

	//compress the tokens into the new tree
	for (size_t i = 0; i < subpass2TokenCount; ++i)
	{
		//check for this line and the next few to be invalid structure and skip it all if so
		if (i + 3 < subpass2TokenCount && subpass2Tokens[i].type == PPC::Stage1::TokenType::BlockComment && subpass2Tokens[i + 1].type == PPC::Stage1::TokenType::Datatype &&
			subpass2Tokens[i + 2].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i + 3].type == PPC::Stage1::TokenType::BlockComment &&
			subpass2Tokens[i + 3].data == " invalid ")
		{
			i += 4; //we add the extra bit to skip the new line
			continue;
		}

		tokens.emplace_back(subpass2Tokens[i]);
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
		//if it's a identifier followed by a colon, we can remove the colon
		//and then mark it's type as JumpLabel
		if (i + 1 < subpass3TokenCount && subpass3Tokens[i].type == PPC::Stage1::TokenType::Identifier &&
			subpass3Tokens[i + 1].type == PPC::Stage1::TokenType::Operator && subpass3Tokens[i + 1].data == ":")
		{
			subpass3Tokens[i].type = PPC::Stage1::TokenType::JumpLabelDefinition;
			tokens.emplace_back(subpass3Tokens[i]);
			subpass3Tokens[i].Print();

			//skip the :
			i++;
		}

		else
		{
			tokens.emplace_back(subpass3Tokens[i]);
			subpass3Tokens[i].Print();
		}
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

	//Subpass 3: Remove Invalid Instructions || read details in the README
	std::vector<PPC::Stage1::Token> subpass3_Tokens = Subpass3_GenerateTokens(subpass2_Tokens);
	subpass2_Tokens.clear();

	//Subpass 4: Jump Labels and Func/Object Names || read details in the README
	std::vector<PPC::Stage1::Token> subpass4_Tokens = Subpass4_GenerateTokens(subpass3_Tokens);
	subpass3_Tokens.clear();

	return subpass4_Tokens;
}