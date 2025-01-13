////#include <PPC/Stage1/Token.hpp>
//
//#include <PPC/Data/PPCInstructions.hpp>
//
////subpasses
//#include <PPC/Stage1/Subpass1.hpp>
//









////processes the subpass 2
//static inline std::vector<PPC::Stage1::Token> Subpass2_GenerateTokens(std::vector<PPC::Stage1::Token>& subpass1Tokens)
//{
//	const size_t subpass1TokenCount = subpass1Tokens.size();
//	std::vector<PPC::Stage1::Token> tokens;
//	tokens.reserve(subpass1TokenCount);
//
//	//compress the tokens into the new tree
//	uint32_t instArrayIndex = 0; PPC::Data::ASM::EInstruction ppcInstrct;
//	for (size_t i = 0; i < subpass1TokenCount; ++i)
//	{
//		//if it's genaric we parse it for furthur data
//		if (subpass1Tokens[i].type == PPC::Stage1::TokenType::Genaric)
//		{
//			//if it's a aligment keyword
//			if (Subpass2_IsKeyword_Alignment(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Alignment;
//			}
//
//			//if it's a global scope keyword
//			else if (Subpass2_IsKeyword_Scope_Global(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Global;
//			}
//
//			//if it's a local scope keyword
//			else if (Subpass2_IsKeyword_Scope_Local(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Local;
//			}
//
//			//if it's a weak scope keyword
//			else if (Subpass2_IsKeyword_Scope_Weak(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Weak;
//			}
//
//			//if it's a hidden scope keyword
//			else if (Subpass2_IsKeyword_Scope_Hidden(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Hidden;
//			}
//
//			//if it's a sym scope keyword
//			else if (Subpass2_IsKeyword_Scope_Sym(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_Scope_Sym;
//			}
//
//			//if it's a sda21 memory offset keyword
//			else if (Subpass2_IsKeyword_MemoryOffset_Sda21(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_Sda21;
//			}
//
//			//if it's a lower bit memory offset keyword
//			else if (Subpass2_IsKeyword_MemoryOffset_LowerBit(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_LowerBit;
//			}
//
//			//if it's a higher bit memory offset keyword
//			else if (Subpass2_IsKeyword_MemoryOffset_HigherBit(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Keyword;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Keyword_MemoryOffset_HigherBit;
//			}
//
//			//if it's a datatype
//			else if (Subpass2_IsDatatype(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Datatype;
//			}
//
//			//if it's a int register
//			else if (Subpass2_IsIntegerRegister(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Int;
//			}
//
//			//if it's a floating register
//			else if (Subpass2_IsFloatingRegister(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Float;
//			}
//
//			//if it's a graphics quantized register
//			else if (Subpass2_IsGraphicsQuantizedRegister(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_GraphicsQuantized;
//			}
//
//			//if it's a condition register
//			else if (Subpass2_IsConditionRegister(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Condition;
//			}
//
//			//if it's a special register
//			else if (Subpass2_IsSpecialRegister(subpass1Tokens[i].data.c_str()))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Register;
//				subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Special;
//			}
//
//			//if it's assembly instruction
//			else if (PPC::Data::ASM::IsASMInstructionStr(subpass1Tokens[i].data.c_str(), instArrayIndex, ppcInstrct))
//			{
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Instruction;
//				//subpass1Tokens[i].specificType = PPC::Stage1::SpecificTokenType::Register_Special;
//			}
//
//			//if it's a digit literal
//
//			//else it's a Identifier
//			else
//				subpass1Tokens[i].type = PPC::Stage1::TokenType::Identifier;
//		}
//
//		//skip the ignore
//		else if (subpass1Tokens[i].type == PPC::Stage1::TokenType::Count)
//		{
//			continue;
//		}
//
//		//if we're not ignoring it and after specififying it's type, we toss it in the new tree
//		tokens.emplace_back(subpass1Tokens[i]);
//	}
//
//	return tokens;
//}
//
////processes the subpass 3
//static inline std::vector<PPC::Stage1::Token> Subpass3_GenerateTokens(std::vector<PPC::Stage1::Token>& subpass2Tokens)
//{
//	const size_t subpass2TokenCount = subpass2Tokens.size();
//	std::vector<PPC::Stage1::Token> tokens;
//	tokens.reserve(subpass2TokenCount);
//
//	//compress the tokens into the new tree
//	for (size_t i = 0; i < subpass2TokenCount; ++i)
//	{
//		//check for this line and the next few to be invalid or illegal structure and skip it all if so
//		if (i + 3 < subpass2TokenCount && subpass2Tokens[i].type == PPC::Stage1::TokenType::BlockComment && subpass2Tokens[i + 1].type == PPC::Stage1::TokenType::Datatype &&
//			subpass2Tokens[i + 2].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i + 3].type == PPC::Stage1::TokenType::BlockComment &&
//			subpass2Tokens[i + 3].data == " invalid " || i + 3 < subpass2TokenCount && subpass2Tokens[i].type == PPC::Stage1::TokenType::BlockComment && subpass2Tokens[i + 1].type == PPC::Stage1::TokenType::Datatype &&
//			subpass2Tokens[i + 2].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i + 3].type == PPC::Stage1::TokenType::BlockComment &&
//			subpass2Tokens[i + 3].data.find("illegal:"))
//		{
//			i += 4; //we add the extra bit to skip the new line
//			continue;
//		}
//
//		//if we're .section,.file or .include or .data remove the whole line
//		else if (subpass2Tokens[i].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i].data == ".section" ||
//			subpass2Tokens[i].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i].data == ".include" ||
//			subpass2Tokens[i].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i].data == ".file" ||
//			subpass2Tokens[i].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i].data == ".data" ||
//			subpass2Tokens[i].type == PPC::Stage1::TokenType::Identifier && subpass2Tokens[i].data == ".text")
//		{
//			while (subpass2Tokens[i].type != PPC::Stage1::TokenType::NewLine && i < subpass2TokenCount)
//			{
//				i++;
//			}
//
//			continue;
//		}
//
//		tokens.emplace_back(subpass2Tokens[i]);
//	}
//
//	return tokens;
//}
//
////processes the subpass 4
//static inline std::vector<PPC::Stage1::Token> Subpass4_GenerateTokens(std::vector<PPC::Stage1::Token>& subpass3Tokens)
//{
//	const size_t subpass3TokenCount = subpass3Tokens.size();
//	std::vector<PPC::Stage1::Token> tokens;
//	tokens.reserve(subpass3TokenCount);
//
//	//compress the tokens into the new tree
//	for (size_t i = 0; i < subpass3TokenCount; ++i)
//	{
//		//if it's a identifier followed by a colon, we can remove the colon
//		//and then mark it's type as JumpLabel
//		if (i + 1 < subpass3TokenCount && subpass3Tokens[i].type == PPC::Stage1::TokenType::Identifier &&
//			subpass3Tokens[i + 1].type == PPC::Stage1::TokenType::Operator && subpass3Tokens[i + 1].data == ":")
//		{
//			subpass3Tokens[i].type = PPC::Stage1::TokenType::JumpLabelDefinition;
//			tokens.emplace_back(subpass3Tokens[i]);
//
//			//skip the :
//			i++;
//		}
//
//		else
//			tokens.emplace_back(subpass3Tokens[i]);
//	}
//
//	return tokens;
//}
//
////processes the subpass 5
//static inline std::vector<PPC::Stage1::Token> Subpass5_StripComments(std::vector<PPC::Stage1::Token>& subpass4Tokens)
//{
//	const size_t subpass4TokenCount = subpass4Tokens.size();
//	std::vector<PPC::Stage1::Token> tokens;
//	tokens.reserve(subpass4TokenCount);
//
//	//compress the tokens into the new tree
//	for (size_t i = 0; i < subpass4TokenCount; ++i)
//	{
//		//if it's a comment, we remove it
//		if (subpass4Tokens[i].type == PPC::Stage1::TokenType::BlockComment || subpass4Tokens[i].type == PPC::Stage1::TokenType::SingleLineComment)
//			continue;
//
//		else
//			tokens.emplace_back(subpass4Tokens[i]);
//	}
//
//	return tokens;
//}
//
////subpass 6 || splitting into expresstions
//static inline std::vector<PPC::Stage1::LexedSingleLineExpresstion> Subpass6_SplitExpresstions(const std::vector<PPC::Stage1::Token>& wholeTokens)
//{
//	//process the entire file into single line expresstions
//	const size_t tokenCount = wholeTokens.size();
//	std::vector<PPC::Stage1::LexedSingleLineExpresstion> singleLines; singleLines.reserve(50);
//	for (size_t t = 0; t < tokenCount; ++t)
//	{
//		//starts a new single line and goes till a new line
//		if (wholeTokens[t].type != PPC::Stage1::TokenType::NewLine)
//		{
//			PPC::Stage1::LexedSingleLineExpresstion* exp = &singleLines.emplace_back(PPC::Stage1::LexedSingleLineExpresstion());
//			exp->tokens.reserve(5);
//
//			while (t < tokenCount && wholeTokens[t].type != PPC::Stage1::TokenType::NewLine)
//			{
//				exp->tokens.emplace_back(wholeTokens[t]);
//				t++;
//			}
//		}
//	}
//
//	//prune the extra new lines
//	size_t singleExpressionCount = singleLines.size();
//	bool weWerePushedBelowZeroLastLoop = false;
//	for (size_t e = 0; e < singleExpressionCount; ++e)
//	{
//		//go back one if needed
//		if (weWerePushedBelowZeroLastLoop)
//		{
//			e = 0;
//			weWerePushedBelowZeroLastLoop = false;
//		}
//
//		//if it's a single line and just a new line, delete it
//		if (singleLines[e].tokens.size() < 2 && singleLines[e].tokens[0].type == PPC::Stage1::TokenType::NewLine || !singleLines[e].tokens.size())
//		{
//			if (e == 0)
//				weWerePushedBelowZeroLastLoop = true;
//
//			singleLines.erase(singleLines.begin() + e);
//			singleExpressionCount--;
//		}
//	}
//
//	//prune the identifiers after the endobj or endfunc
//	singleExpressionCount = singleLines.size();
//	for (size_t e = 0; e < singleExpressionCount; ++e)
//	{
//		if (singleLines[e].tokens.size() == 2 && singleLines[e].tokens[0].type == PPC::Stage1::TokenType::Keyword &&
//			singleLines[e].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_FuncEnd
//			|| singleLines[e].tokens.size() == 2 && singleLines[e].tokens[0].type == PPC::Stage1::TokenType::Keyword &&
//			singleLines[e].tokens[0].specificType == PPC::Stage1::SpecificTokenType::Keyword_ObjEnd)
//			singleLines[e].tokens.resize(1);
//	}
//
//	return singleLines;
//	
//}
//
////lexes ASM into tokens
//PPC::Stage1::LexedFile PPC::Stage1::LexTokens(const Data::CompilerSettings& settings, const std::string& code)
//{
//	//Subpass 1: Genaric Token Splits || read details in the README
//	LexedFile file;
//	std::vector<Token> wholeTokens = Subpass1_GenerateGeneralTokens(code);	
//
//	//Subpass 2:  Keywords and fine typing || read details in the README
//	wholeTokens = Subpass2_GenerateTokens(wholeTokens);
//
//	//Subpass 3: Remove Invalid Instructions And Section Info || read details in the README
//	wholeTokens = Subpass3_GenerateTokens(wholeTokens);
//
//	//Subpass 4: Jump Labels || read details in the README
//	wholeTokens = Subpass4_GenerateTokens(wholeTokens);
//
//	//Subpass 5: Strip comments
//	wholeTokens = Subpass5_StripComments(wholeTokens);
//
//	//splits the token stream into per-line expresstions
//	file.singleLineExpesstions = Subpass6_SplitExpresstions(wholeTokens);
//	wholeTokens.clear();
//
//	return file;
//}