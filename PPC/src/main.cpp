/*
Power PC transcompiler || created by Sean Mott 2024+

Allows a Game Cube/Wii ROM to be converted to C++
*/


#include <PPC/Data/ASMFile.hpp>

#include <PPC/Stage1/Token.hpp>
#include <PPC/Stage2/IR.hpp>

//the modes PPC can be in
enum class PPCMode
{
	Full = 0, //the default mode and will take the entire ROM and convert it to C++
	
	ASMType, //takes a ROM and generates the ASM then gives it type info but stays in ASM
};


//entry point
int main(int args, const char* argv[])
{
	//parse flags
	PPC::Data::CompilerSettings settings;
	settings.outputDebugASM = true;

	//loads the code
	const std::string ASMDirectory = "C:/Decomps/TOD-Decomp/RawASM/asm/";
	std::vector<std::string> ASMFiles; ASMFiles.reserve(5);
	for (const auto& entry : std::filesystem::directory_iterator(ASMDirectory))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".s") {
			ASMFiles.emplace_back(entry.path().string());
		}
	}
	//const std::string ASMFileName = "auto_00_80003100_init";
	//const std::string ASMFileName = "auto_05_80047290_data";
	//const std::string ASMFileName = "__init_cpp_exceptions";
	//const std::string ASMFileName = "auto_01_800056A0_text";
	for (size_t i = 0; i < ASMFiles.size(); ++i)
	{
		PPC::Data::ASMFile ASMFile;
		ASMFile.SetASM(ASMFiles[i]);
		ASMFile.LoadASM();

		//lexes assembly into tokens	
		PPC::Stage1::LexedFile f = PPC::Stage1::LexTokens(settings, ASMFile.code);

		//generates the IR
		std::vector<PPC::Stage2::Node> nodes = PPC::Stage2::ParseExpresstionsIntoNodeIR(f.singleLineExpesstions);
		std::string debugIR = "";
		for (size_t i = 0; i < nodes.size(); ++i)
			debugIR += nodes[i].GenerateDebugIR();

		//spits out a debug IR file
		ASMFiles[i][ASMFiles[i].size() - 1] = 'c';
		std::fstream debugIRFile(ASMFiles[i], std::ios::out);
		debugIRFile.write(debugIR.c_str(), debugIR.size());
	}

	//getchar();
	return 0;
}