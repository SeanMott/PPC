#include <DTK_PPC_Lexer/Lexer.hpp>

#define FMT_HEADER_ONLY
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/color.h"
#include "C:/Compilers/PPC/Venders/fmt/include/fmt/core.h"

#include <DTK_PowerPCDecoder/AssemblyInstructions.hpp>
#include <DTK_PowerPCDecoder/Registers.hpp>

//prints genaric line info
static inline void PrintGenaricDataInfo(const size_t& lineCount, const std::string& data)
{
	//prints line info
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print("{}\n", data);
}

//creates a ASM info comment || a little bit of info on sector and byte size DTK adds
static inline void GenerateToken_ASMIntelComment(const size_t& lineCount, const std::string& data)
{
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print(fg(fmt::color::green), "ASM Extra Info: {}\n", data);
}

//creates a ASM intruction address comment
static inline void GenerateToken_InstructionAddressComment(const size_t& lineCount, const std::string& data)
{
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print(fg(fmt::color::green), "ASM Instruction Address: /* {}\n", data);
}

//creates a string literal token
static inline void GenerateToken_StringLiteral(const size_t& lineCount, const std::string& data)
{
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print(fg(fmt::color::pink), "String: \"{}\"\n", data);
}

//creates a dot directive token
static inline void GenerateToken_DotDirective(const size_t& lineCount, const std::string& data)
{
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print(fg(fmt::color::dark_golden_rod), "Dot Directive: {}\n", data);
}

//creates a operator token
static inline void GenerateToken_Operator(const size_t& lineCount, const char op)
{
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print(fg(fmt::color::rebecca_purple), "Operator: {}\n", op);
}

//creates a digit literal token
static inline void GenerateToken_DigitLiteral(const size_t& lineCount, const std::string& data)
{
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print(fg(fmt::color::olive), "Digit: {}\n", data);
}

//creates a hex literal token
static inline void GenerateToken_HexLiteral(const size_t& lineCount, const std::string& data)
{
	fmt::print(fg(fmt::color::cyan), "Line: {}", lineCount);
	fmt::print(fg(fmt::color::fire_brick), " || ");
	fmt::print(fg(fmt::color::olive), "Hex: {}\n", data);
}


//creates a genaric token

//creates a sector dot directive

//creates a aligment dot directive

//checks if something is a digit
static inline bool IsDigit(const char* str)
{
	char* p;
	long converted = strtol(str, &p, 10);
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
	//checks for hex
	if (hexStr.size() < 2 || hexStr[0] != '0' || hexStr[1] != 'x')
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

//process a chunk of data
static inline bool ProcessData(const size_t& lineCount, std::string& data)
{
	if (data.empty()) //if there's no data
		return false;

	bool found = false;

	//if data is a dot directive
	if (data[0] == '.')
	{
		GenerateToken_DotDirective(lineCount, data);
		found = true;
	}

	//if data is a keyword

	//if data is a register

	//if data is a instruction

	//if it's a digit literal
	else if (IsDigit(data.c_str()))
	{
		GenerateToken_DigitLiteral(lineCount, data);
		found = true;
	}

	//if it's a hex literal
	else if (IsHex(data.c_str()))
	{
		GenerateToken_HexLiteral(lineCount, data);
		found = true;
	}

	//if it's a float/double

	//if it's a integer

	//if nothing print genaric
	else
		PrintGenaricDataInfo(lineCount, data);

	data = "";

	return found;
}

//defines a parser for DTK Assembly
void PPC::Frontend::DTK::ASMParser(const std::string& code)
{
	const size_t codeLength = code.size();

	bool isInQuotes = false; //are we inside quoates

	//breaks the code into lines
	std::string data = ""; size_t lineCount = 1;
	for (size_t c = 0; c < codeLength; ++c)
	{
		//skips tabs
		if (code[c] == '\t')
			continue;

		//new line
		if (code[c] == '\n')
		{
			//process previous data if anything is left
			ProcessData(lineCount, data);

			//moves to next line
			lineCount++;
			continue;
		}

		//if space or comma process the data
		if (code[c] == ' ' || code[c] == ',')
			ProcessData(lineCount, data);

		//if operator ( or ) or @ or -
		else if (code[c] == '(' || code[c] == ')' || code[c] == '@' || code[c] == '-')
		{
			//process previous data if anything is left
			ProcessData(lineCount, data);

			GenerateToken_Operator(lineCount, code[c]);
			continue;
		}

		//if we start a #, it's a start of a ASM extra intel comment, we go till the end of the line
		else if (code[c] == '#')
		{
			//process previous data if anything is left
			ProcessData(lineCount, data);

			//process current comment
			while (code[c] != '\n')
			{
				c++;
				data += code[c];
			}
			GenerateToken_ASMIntelComment(lineCount, data);
			data = "";

			continue;
		}

		//if it starts a /*, it's a start of a address comment, go until */
		else if (code[c] == '/' && code[c + 1] == '*')
		{
			//process previous data if anything is left
			ProcessData(lineCount, data);

			//process current comment
			c++; //skip the first / so we don't instantly break out
			while (code[c] != '/')
			{
				c++;
				data += code[c];
			}
			GenerateToken_InstructionAddressComment(lineCount, data);
			data = "";

			continue;
		}

		//if it's a "" string
		else if (code[c] == '"')
		{
			//process previous data if anything is left
			ProcessData(lineCount, data);

			//process current string
			c++; //skip the first " so we don't instantly break out
			while (code[c] != '"')
			{
				data += code[c];
				c++;
			}
			GenerateToken_StringLiteral(lineCount, data);
			data = "";

			continue;
		}

		//adds data
		else
			data += code[c];
	}
}