/*
PPC - Power PC To C Compiler

WIP Transcompiler for converting Game Cube Assembly to C++

*/

#include <string>
#include <filesystem>
#include <process.h>

//calculates the position of what programs to use
const std::string workingDir = std::filesystem::current_path().string();

//change per platform
const std::string python = "C:/Compilers/PPC/tools/Windows_X64/Python_3.12.4/python.exe";

const std::string ninja = "C:/Compilers/PPC/tools/Windows_X64/ninja.exe";

const std::string dtk = "C:/Compilers/PPC/tools/Windows_X64/dtk.exe";

const std::string git = "C:/Compilers/PPC/tools/Windows_X64/Git/git";

//fixes a ROM
static inline void Tool_FixROM(const std::string& ROMPath, std::string outputROMPath)
{
	//fixes the ROM
	std::string pythonCommand = python + " Scripts/DTK_FixISO.py " + ROMPath + " " + outputROMPath;
	system(pythonCommand.c_str());
}

//performs stage 0
static inline void Stage_Zero(const std::string& ROMPath, const std::string& projectDir)
{
	//validate ROM

	//runs stage 0
	std::string pythonCommand = python + " Scripts/Stage0.py " + python + " " + ninja + " " + dtk + " " + git + " " + projectDir + " " + ROMPath;
	system(pythonCommand.c_str());
}

//performs stage 1
static inline void Stage_One()
{
	//consume Assembly

	//generate metadata
}

//if no arguments are passed
static inline void Help()
{
	
}

//entry point
int main(int args, const char* argv)
{
	//--arg

	//std::string projectPath = "\"C:/Users/rafal/Desktop/Tower of Druaga, The (Japan)\"";
	//std::string ROMPath = "\"C:/Users/rafal/Desktop/Tower of Druaga, The (Japan)/TOD.iso\"";

	std::string projectPath = "\"C:/Users/rafal/Desktop/Kirby Air Ride [GKYE01]\"";
	std::string ROMPath = "\"C:/Users/rafal/Desktop/Kirby Air Ride [GKYE01]/game.iso\"";

	//"fixes" ROM
	//Tool_FixROM(ROMPath, "\"C:/Users/rafal/Desktop/Godzilla - Destroy All Monsters Melee (USA)/Godzilla_:3.iso\"");
	//ROMPath = "\"C:/Users/rafal/Desktop/Godzilla - Destroy All Monsters Melee (USA)/Godzilla_:3.iso\"";

	//perform stage 0
	Stage_Zero(ROMPath, projectPath);

	//--clean up

	getchar();
	return 0;
}