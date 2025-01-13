#pragma once

//defines datatypes used accros the tools

namespace PPC::Data::Datatype
{
	//defines a datatype in DTK
	enum class DTKDatatype
	{
		Skip = 0, //a skip datatype, we normally use it as space reserving. We map it to a uint32
		Byte4, //this can generally be anything, either a uint16 or a void*
		Byte2, //double of a char
		Byte, //this is a char

		Float, //it's a float
		Double, //it's a double floating

		String, //a string

		Rel, //defines a relocation
	};

	//defines the datatype for a internal datatype in PPC
	enum class Datatype
	{

	};
}