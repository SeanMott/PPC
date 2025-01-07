#pragma once

//defines scope for a ASM

namespace PPC::Data
{
	//lists the scope keywords

	//defines a scope type
	enum class ScopeKeyword
	{
		Global = 0,
		Local,
		Weak,

		Count
	};

	//is the keyword a scope keyword
}