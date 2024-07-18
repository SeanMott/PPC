#include <DTK_PPC_Lexer/Lexer.hpp>

//prints token data
std::string PPC::Frontend::DTK::Token::Print() const
{
	std::string output = "";

	switch (type)
	{
	case TokenType::Identifier:
		//prints line info
		fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
		fmt::print(fg(fmt::color::fire_brick), " || ");
		fmt::print("Identitfier: {}\n", data);
		output = fmt::format("Line: {} || Identitfier: {}\n", lineCount, data);
		break;

		case TokenType::Comment_ASMIntel:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::green), "ASM Extra Info: {}\n", data);
			output = fmt::format("Line: {} || ASM Extra Info: {}\n", lineCount, data);
			break;
		case TokenType::Comment_ASMInstructionAddress:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::green), "ASM Instruction Address: /* {}\n", data);
			output = fmt::format("Line: {} || ASM Instruction Address: {}\n", lineCount, data);
			break;

		case TokenType::Literal_Integer:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::olive), "Integer Literal: {}\n", data);
			output = fmt::format("Line: {} || Integer Literal: {}\n", lineCount, data);
			break;
		case TokenType::Literal_Float:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::olive), "Float Literal: {}\n", data);
			output = fmt::format("Line: {} || Float Literal: {}\n", lineCount, data);
			break;

		case TokenType::Literal_Hex:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::olive), "Hex Literal: {}\n", data);
			output = fmt::format("Line: {} || Hex Literal: {}\n", lineCount, data);
			break;
		case TokenType::Literal_String:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::pink), "String Literal: \"{}\"\n", data);
			output = fmt::format("Line: {} || String Literal: {}\n", lineCount, data);
			break;

		case TokenType::Register_Int:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::dark_salmon), "Int Register: {}\n", data);
			output = fmt::format("Line: {} || Int Register: {}\n", lineCount, data);
			break;
		case TokenType::Register_Float:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::dark_salmon), "Float Register: {}\n", data);
			output = fmt::format("Line: {} || Float Register: {}\n", lineCount, data);
			break;
		case TokenType::Register_Keyword:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::dark_salmon), "Keyword Register: {}\n", data);
			output = fmt::format("Line: {} || Keyword Register: {}\n", lineCount, data);
			break;

		case TokenType::DotDirective_Keyword:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::dark_golden_rod), "Dot Directive: {}\n", data);
			output = fmt::format("Line: {} || Dot Directive: {}\n", lineCount, data);
			break;
		case TokenType::DotDirective_Datatype:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::dark_golden_rod), "Dot Directive Datatype: {}\n", data);
			output = fmt::format("Line: {} || Dot Directive Datatype: {}\n", lineCount, data);
			break;
		case TokenType::BitDirective:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::lemon_chiffon), "Bit Directive: {}\n", data);
			output = fmt::format("Line: {} || Bit Directive: {}\n", lineCount, data);
			break;

		case TokenType::Operator:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::rebecca_purple), "Operator: {}\n", data);
			output = fmt::format("Line: {} || Operator: {}\n", lineCount, data);
			break;

		case TokenType::ASMInstruction:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::orange), "ASM Instruction: {}\n", data);
			output = fmt::format("Line: {} || ASM Instruction: {}\n", lineCount, data);
			break;

		case TokenType::ScopeKeyword:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::dark_gray), "Scope Keyword: {}\n", data);
			output = fmt::format("Line: {} || Scope Keyword: {}\n", lineCount, data);
			break;

		case TokenType::Newline:
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print(fg(fmt::color::aqua), "New Line: {}\n", data);
			output = fmt::format("Line: {} || New Line: {}\n", lineCount, data);
			break;

		default:
			//prints line info
			fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
			fmt::print(fg(fmt::color::fire_brick), " || ");
			fmt::print("UNKNOWN TOKEN: {}\n", data);
			output = fmt::format("Line: {} || UNKNOWN TOKEN: {}\n", lineCount, data);
			break;
	}

	return output;
}

//checks if something is a digit
static inline bool IsDigit(const std::string& data)
{
	if (data.empty()) //if there's no data
		return false;

	char* p;
	long converted = strtol(data.c_str(), &p, 10);
	if (*p) {
		return false;
	}
	else {
		return true;
	}
}

//checks if something is a hex value
static inline bool IsHex(const std::string& hexStr)
{
	if (hexStr.empty()) //if there's no data
		return false;

	//checks for hex
	if (hexStr.size() < 3 || hexStr[0] != '0' || hexStr[1] != 'x')
		return false;

	//shave off the hex part
	std::string hexValue = hexStr;
	hexValue.erase(0); hexValue.erase(0);

	char* p;
	long converted = strtol(hexValue.c_str(), &p, 10);
	if (*p) {
		return false;
	}
	else {
		return true;
	}
}

//checks if it's a floating number
static inline bool isFloatNumber(const std::string& string) {
	std::string::const_iterator it = string.begin();
	bool decimalPoint = false;
	int minSize = 0;
	if (string.size() > 0 && (string[0] == '-' || string[0] == '+')) {
		it++;
		minSize++;
	}
	while (it != string.end()) {
		if (*it == '.') {
			if (!decimalPoint) decimalPoint = true;
			else break;
		}
		else if (!std::isdigit(*it) && ((*it != 'f') || it + 1 != string.end() || !decimalPoint)) {
			break;
		}
		++it;
	}
	return string.size() > minSize && it == string.end();
}

static inline PPC::Frontend::DTK::Token GenerateToken_Identifier(const size_t& lineCount, const std::string& data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Identifier;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_DotDirective(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::DotDirectives::DotDirective_Keyword& directive)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::DotDirective_Keyword;
	t.dotDirective = directive;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_DotDirectiveDatatype(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::DotDirectives::DotDirective_Datatype& datatype)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::DotDirective_Datatype;
	t.datatype = datatype;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_BitDirective(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::BitDirectives::BitDirectiveType& bitDirective)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::BitDirective;
	t.bitDirective = bitDirective;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_ScopeKeyword(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::Scope::ScopeType scope)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::ScopeKeyword;
	t.scope = scope;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_IntRegister(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::Register::IntegerGeneralPurposeRegister& reg)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Register_Int;
	t.intRegister = reg;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_FloatRegister(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::Register::FloatingGeneralPurposeRegister& reg)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Register_Float;
	t.floatRegister = reg;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_KeywordRegister(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::Register::Register_Keword_Enum& reg)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Register_Keyword;
	t.keywordRegister = reg;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_ASMInstruction(const size_t& lineCount, const std::string& data,
	const PPC::Decoder::ASM::EInstruction& inst)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::ASMInstruction;
	t.instruction = inst;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Literal_Hex(const size_t& lineCount, const std::string& data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Literal_Hex;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Literal_Integer(const size_t& lineCount, const std::string& data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Literal_Integer;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Literal_Float(const size_t& lineCount, const std::string& data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Literal_Float;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Literal_String(const size_t& lineCount, const std::string& data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Literal_String;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Comment_ASMIntel(const size_t& lineCount, const std::string& data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Comment_ASMIntel;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Comment_ASMInstructionAddress(const size_t& lineCount, const std::string& data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Comment_ASMInstructionAddress;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Operator(const size_t& lineCount, const char data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Operator;
	return t;
}

static inline PPC::Frontend::DTK::Token GenerateToken_Newline(const size_t& lineCount, const char data)
{
	PPC::Frontend::DTK::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = PPC::Frontend::DTK::TokenType::Newline;
	return t;
}

//process a chunk of data
static inline bool ProcessData(const size_t& lineCount, std::string& data, PPC::Frontend::DTK::Token& token)
{
	if (data.empty()) //if there's no data
		return false;

	bool found = false;

	uint32_t arrayIndex = 0; 
	PPC::Decoder::ASM::EInstruction instruction; 
	PPC::Decoder::Register::IntegerGeneralPurposeRegister intRegister; PPC::Decoder::Register::FloatingGeneralPurposeRegister floatRegister;
	PPC::Decoder::Register::Register_Keword_Enum keywordRegister;
	PPC::Decoder::DotDirectives::DotDirective_Keyword dotDirective;
	PPC::Decoder::DotDirectives::DotDirective_Datatype datatype;
	PPC::Decoder::BitDirectives::BitDirectiveType bitDirective;
	PPC::Decoder::Scope::ScopeType scope;

	//-----if data is a dot directive
	if (PPC::Decoder::DotDirectives::IsDotDirectiveKeyword(data.c_str(), arrayIndex, dotDirective))
	{
		token = GenerateToken_DotDirective(lineCount, data, dotDirective);
		found = true;
	}

	//-----if it's a datatype
	else if (PPC::Decoder::DotDirectives::IsDotDirectiveDatatype(data.c_str(), arrayIndex, datatype))
	{
		token = GenerateToken_DotDirectiveDatatype(lineCount, data, datatype);
		found = true;
	}

	//-----if it's a bit directive
	else if (PPC::Decoder::BitDirectives::IsBitDirective(data.c_str(), arrayIndex, bitDirective))
	{
		token = GenerateToken_BitDirective(lineCount, data, bitDirective);
		found = true;
	}

	//scope keyword
	else if (PPC::Decoder::Scope::IsScopeKeyword(data.c_str(), arrayIndex, scope))
	{
		token = GenerateToken_ScopeKeyword(lineCount, data, scope);
		found = true;
	}

	//if data is a int register
	else if (PPC::Decoder::Register::IsString_GeneralIntegerRegister(data.c_str(), arrayIndex, intRegister))
	{
		token = GenerateToken_IntRegister(lineCount, data, intRegister);
		found = true;
	}

	//if data is a floating register
	else if (PPC::Decoder::Register::IsString_GeneralFloatingRegister(data.c_str(), arrayIndex, floatRegister))
	{
		token = GenerateToken_FloatRegister(lineCount, data, floatRegister);
		found = true;
	}

	//if data is a keyword register
	else if (PPC::Decoder::Register::IsKeywordRegister(data.c_str(), arrayIndex, keywordRegister))
	{
		token = GenerateToken_KeywordRegister(lineCount, data, keywordRegister);
		found = true;
	}

	//if data is a instruction
	else if (PPC::Decoder::ASM::IsASMInstructionStr(data.c_str(), arrayIndex, instruction))
	{
		token = GenerateToken_ASMInstruction(lineCount, data, instruction);
		found = true;
	}

	//if it's a digit literal
	else if (IsDigit(data.c_str()))
	{
		token = GenerateToken_Literal_Integer(lineCount, data);
		found = true;
	}

	//if it's a hex literal
	else if (IsHex(data.c_str()))
	{
		token = GenerateToken_Literal_Hex(lineCount, data);
		found = true;
	}

	//if it's a float
	else if (isFloatNumber(data))
	{
		token = GenerateToken_Literal_Float(lineCount, data);
		found = true;
	}

	//if nothing print genaric
	else
	{
		token = GenerateToken_Identifier(lineCount, data);
		found = true;
	}

	data = "";

	return found;
}

//defines a parser for DTK Assembly
std::vector<PPC::Frontend::DTK::Token> PPC::Frontend::DTK::ASMParser(const std::string& code)
{
	const size_t codeLength = code.size();

	std::vector<Token> tokens; tokens.reserve(codeLength);
	Token t;

	//breaks the code into lines
	std::string data = ""; size_t lineCount = 1;
	for (size_t c = 0; c < codeLength; ++c)
	{
		//skips tabs
		if (code[c] == '\t')
		{
			//process previous data if anything is left
			if (ProcessData(lineCount, data, t))
				tokens.emplace_back(t);

			continue;
		}

		//new line
		if (code[c] == '\n')
		{
			//process previous data if anything is left
			if (ProcessData(lineCount, data, t))
				tokens.emplace_back(t);

			//moves to next line
			tokens.emplace_back(GenerateToken_Newline(lineCount, '\n'));
			lineCount++;
			continue;
		}

		//if we start a #, it's a start of a ASM extra intel comment, we go till the end of the line
		else if (code[c] == '#')
		{
			//process previous data if anything is left
			if (ProcessData(lineCount, data, t))
				tokens.emplace_back(t);

			//process current comment
			while (code[c] != '\n')
			{
				c++;
				data += code[c];
			}
			tokens.emplace_back(GenerateToken_Comment_ASMIntel(lineCount, data));
			data = "";

			continue;
		}

		//if it starts a /*, it's a start of a address comment, go until */
		else if (code[c] == '/' && c + 1 <= codeLength && code[c + 1] == '*')
		{
			//process previous data if anything is left
			if (ProcessData(lineCount, data, t))
				tokens.emplace_back(t);

			//process current comment
			c++; //skip the first / so we don't instantly break out
			while (code[c] != '/')
			{
				c++;
				data += code[c];
			}
			tokens.emplace_back(GenerateToken_Comment_ASMInstructionAddress(lineCount, data));
			data = "";

			continue;
		}

		//if space process the data
		if (code[c] == ' ')
		{
			if (ProcessData(lineCount, data, t))
				tokens.emplace_back(t);
		}

		//if operator ( or ) or @ or - or + or ,
		else if (code[c] == '(' || code[c] == ')' || code[c] == '@' || code[c] == '-' || code[c] == '+' || code[c] == ',')
		{
			//process previous data if anything is left
			if (ProcessData(lineCount, data, t))
				tokens.emplace_back(t);

			tokens.emplace_back(GenerateToken_Operator(lineCount, code[c]));
			continue;
		}

		//if it's a "" string
		else if (code[c] == '"')
		{
			//process previous data if anything is left
			if (ProcessData(lineCount, data, t))
				tokens.emplace_back(t);

			//process current string
			c++; //skip the first " so we don't instantly break out
			while (code[c] != '"')
			{
				data += code[c];

				//if it's a back slash, append another
				if (code[c] == '\\')
					data += '\\';

				c++;
			}
			tokens.emplace_back(GenerateToken_Literal_String(lineCount, data));
			data = "";

			continue;
		}

		//adds data
		else
			data += code[c];
	}

	return tokens;
}