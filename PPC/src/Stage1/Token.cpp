#include <PPC/Stage1/Token.hpp>

size_t lineCount = 1, charCount = 0;

//parses raw code into Genaric Tokens for Subpass 1
//read the Subpass 1: Genaric Token Splits in the README
static inline std::vector<PPC::Stage1::Token> Subpass1_GenerateGeneralTokens(const std::string& rawCode)
{
	const size_t codeLength = rawCode.size();
	std::vector<PPC::Stage1::Token> subpass1_Tokens;
	subpass1_Tokens.reserve(20);

	//goes through the code


	return subpass1_Tokens;
}

//lexes ASM into tokens
std::vector<PPC::Stage1::Token> PPC::Stage1::LexTokens(const Data::TranslationUnit& tu)
{
	//Subpass 1: Genaric Token Splits || read details in the README
	std::vector<PPC::Stage1::Token> subpass1_Tokens;

	std::vector<PPC::Stage1::Token> tokens;

	return tokens;
}