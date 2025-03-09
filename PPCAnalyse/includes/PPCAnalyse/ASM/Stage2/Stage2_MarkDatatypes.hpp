#pragma once

//marks datatypes allocated in a struct or a func for padding

#include <PPCLib/Token/Token.hpp>

#include <PPCLib/Data/Datatypes.h>

namespace PPC::Analyse::ASM::Stage2::Subpass
{
	inline void PerformSubpass_MarkDataBytes(std::vector<PPC::Token::Token>& tokens)
	{
		//gets the datatype
		size_t tokenCount = tokens.size();
		for (size_t i = 0; i < tokenCount; ++i)
		{
			if (tokens[i].type == PPC::Token::TokenType::Genaric)
			{
				if (PPC::Data::Datatype::IsASMKeyword_Datatype(tokens[i].data.c_str(), tokens[i].dataForSpecificTokenTypes.datatype))
					tokens[i].type = PPC::Token::TokenType::Datatype;
			}
		}
	}
}